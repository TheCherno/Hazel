//	MIT License
//	
//	Copyright(c) 2017 Thomas Monkman
//	
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//	
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <Pathcch.h>
#include <shlwapi.h>
#endif // WIN32

#if __unix__
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#endif // __unix__

#include <functional>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <vector>
#include <array>
#include <map>
#include <system_error>
#include <string>
#include <algorithm>
#include <type_traits>
#include <future>
#include <regex>
#include <iostream>

namespace filewatch {
	enum class Event {
		added,
		removed,
		modified,
		renamed_old,
		renamed_new
	};

	/**
	* \class FileWatch
	*
	* \brief Watches a folder or file, and will notify of changes via function callback.
	*
	* \author Thomas Monkman
	*
	*/
	template<class T>
	class FileWatch
	{
		typedef typename T::value_type C;
		typedef std::basic_string<C, std::char_traits<C>> UnderpinningString;
		typedef std::basic_regex<C, std::regex_traits<C>> UnderpinningRegex;

	public:

		FileWatch(T path, UnderpinningRegex pattern, std::function<void(const T& file, const Event event_type)> callback) :
			_path(path),
			_pattern(pattern),
			_callback(callback),
			_directory(get_directory(path))
		{
			init();
		}

		FileWatch(T path, std::function<void(const T& file, const Event event_type)> callback) :
			FileWatch<T>(path, UnderpinningRegex(_regex_all), callback) {}

		~FileWatch() {
			destroy();
		}

		FileWatch(const FileWatch<T>& other) : FileWatch<T>(other._path, other._callback) {}

		FileWatch<T>& operator=(const FileWatch<T>& other) 
		{
			if (this == &other) { return *this; }

			destroy();
			_path = other._path;
			_callback = other._callback;
			_directory = get_directory(other._path);
			init();
			return *this;
		}

		// Const memeber varibles don't let me implent moves nicely, if moves are really wanted std::unique_ptr should be used and move that.
		FileWatch<T>(FileWatch<T>&&) = delete;
		FileWatch<T>& operator=(FileWatch<T>&&) & = delete;

	private:
		static constexpr C _regex_all[] = { '.', '*', '\0' };
		static constexpr C _this_directory[] = { '.', '/', '\0' };

		struct PathParts
		{
			PathParts(T directory, T filename) : directory(directory), filename(filename) {}
			T directory;
			T filename;
		};
		const T _path;

		UnderpinningRegex _pattern;

		static constexpr std::size_t _buffer_size = { 1024 * 256 };

		// only used if watch a single file
		bool _watching_single_file = { false };
		T _filename;

		std::atomic<bool> _destory = { false };
		std::function<void(const T& file, const Event event_type)> _callback;

		std::thread _watch_thread;

		std::condition_variable _cv;
		std::mutex _callback_mutex;
		std::vector<std::pair<T, Event>> _callback_information;
		std::thread _callback_thread;

		std::promise<void> _running;
#ifdef _WIN32
		HANDLE _directory = { nullptr };
		HANDLE _close_event = { nullptr };

		const DWORD _listen_filters =
			FILE_NOTIFY_CHANGE_SECURITY |
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_LAST_ACCESS |
			FILE_NOTIFY_CHANGE_LAST_WRITE |
			FILE_NOTIFY_CHANGE_SIZE |
			FILE_NOTIFY_CHANGE_ATTRIBUTES |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_FILE_NAME;

		const std::map<DWORD, Event> _event_type_mapping = {
			{ FILE_ACTION_ADDED, Event::added },
			{ FILE_ACTION_REMOVED, Event::removed },
			{ FILE_ACTION_MODIFIED, Event::modified },
			{ FILE_ACTION_RENAMED_OLD_NAME, Event::renamed_old },
			{ FILE_ACTION_RENAMED_NEW_NAME, Event::renamed_new }
		};
#endif // WIN32

#if __unix__
		struct FolderInfo {
			int folder;
			int watch;
		};

		FolderInfo  _directory;

		const std::uint32_t _listen_filters = IN_MODIFY | IN_CREATE | IN_DELETE;

		const static std::size_t event_size = (sizeof(struct inotify_event));
#endif // __unix__

		void init() 
		{
#ifdef _WIN32
			_close_event = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (!_close_event) {
				throw std::system_error(GetLastError(), std::system_category());
			}
#endif // WIN32
			_callback_thread = std::move(std::thread([this]() {
				try {
					callback_thread();
				} catch (...) {
					try {
						_running.set_exception(std::current_exception());
					}
					catch (...) {} // set_exception() may throw too
				}
			}));
			_watch_thread = std::move(std::thread([this]() { 
				try {
					monitor_directory();
				} catch (...) {
					try {
						_running.set_exception(std::current_exception());
					}
					catch (...) {} // set_exception() may throw too
				}
			}));

			std::future<void> future = _running.get_future();
			future.get(); //block until the monitor_directory is up and running
		}

		void destroy()
		{
			_destory = true;
			_running = std::promise<void>();
#ifdef _WIN32
			SetEvent(_close_event);
#elif __unix__
			inotify_rm_watch(_directory.folder, _directory.watch);
#endif // __unix__
			_cv.notify_all();
			_watch_thread.join();
			_callback_thread.join();
#ifdef _WIN32
			CloseHandle(_directory);
#elif __unix__
			close(_directory.folder);
#endif // __unix__
		}

		const PathParts split_directory_and_file(const T& path) const 
		{
			const auto predict = [](C character) {
#ifdef _WIN32
				return character == C('\\') || character == C('/');
#elif __unix__
				return character == C('/');
#endif // __unix__
			};

			UnderpinningString path_string = path;
			const auto pivot = std::find_if(path_string.rbegin(), path_string.rend(), predict).base();
			//if the path is something like "test.txt" there will be no directory part, however we still need one, so insert './'
			const T directory = [&]() {
				const auto extracted_directory = UnderpinningString(path_string.begin(), pivot);
				return (extracted_directory.size() > 0) ? extracted_directory : UnderpinningString(_this_directory);
			}();
			const T filename = UnderpinningString(pivot, path_string.end());
			return PathParts(directory, filename);
		}

		bool pass_filter(const UnderpinningString& file_path)
		{ 
			if (_watching_single_file) {
				const UnderpinningString extracted_filename = { split_directory_and_file(file_path).filename };
				//if we are watching a single file, only that file should trigger action
				return extracted_filename == _filename;
			}
			return std::regex_match(file_path, _pattern);
		}

#ifdef _WIN32
		template<typename... Args> DWORD GetFileAttributesX(const char* lpFileName, Args... args) {
			return GetFileAttributesA(lpFileName, args...);
		}
		template<typename... Args> DWORD GetFileAttributesX(const wchar_t* lpFileName, Args... args) {
			return GetFileAttributesW(lpFileName, args...);
		}

		template<typename... Args> HANDLE CreateFileX(const char* lpFileName, Args... args) {
			return CreateFileA(lpFileName, args...);
		}
		template<typename... Args> HANDLE CreateFileX(const wchar_t* lpFileName, Args... args) {
			return CreateFileW(lpFileName, args...);
		}

		HANDLE get_directory(const T& path) 
		{
			auto file_info = GetFileAttributesX(path.c_str());

			if (file_info == INVALID_FILE_ATTRIBUTES)
			{
				throw std::system_error(GetLastError(), std::system_category());
			}
			_watching_single_file = (file_info & FILE_ATTRIBUTE_DIRECTORY) == false;

			const T watch_path = [this, &path]() {
				if (_watching_single_file)
				{
					const auto parsed_path = split_directory_and_file(path);
					_filename = parsed_path.filename;
					return parsed_path.directory;
				}
				else 
				{
					return path;
				}
			}();

			HANDLE directory = CreateFileX(
				watch_path.c_str(),           // pointer to the file name
				FILE_LIST_DIRECTORY,    // access (read/write) mode
				FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // share mode
				nullptr, // security descriptor
				OPEN_EXISTING,         // how to create
				FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, // file attributes
				HANDLE(0));                 // file with attributes to copy

			if (directory == INVALID_HANDLE_VALUE)
			{
				throw std::system_error(GetLastError(), std::system_category());
			}
			return directory;
		}

		void convert_wstring(const std::wstring& wstr, std::string& out)
		{
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
			out.resize(size_needed, '\0');
			WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &out[0], size_needed, NULL, NULL);
		}

		void convert_wstring(const std::wstring& wstr, std::wstring& out)
		{
			out = wstr;
		}

		void monitor_directory() 
		{
			std::vector<BYTE> buffer(_buffer_size);
			DWORD bytes_returned = 0;
			OVERLAPPED overlapped_buffer{ 0 };

			overlapped_buffer.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (!overlapped_buffer.hEvent) {
				std::cerr << "Error creating monitor event" << std::endl;
			}

			std::array<HANDLE, 2> handles{ overlapped_buffer.hEvent, _close_event };

			auto async_pending = false;
			_running.set_value();
			do {
				std::vector<std::pair<T, Event>> parsed_information;
				ReadDirectoryChangesW(
					_directory,
					buffer.data(), static_cast<DWORD>(buffer.size()),
					TRUE,
					_listen_filters,
					&bytes_returned,
					&overlapped_buffer, NULL);
			
				async_pending = true;
			
				switch (WaitForMultipleObjects(2, handles.data(), FALSE, INFINITE))
				{
				case WAIT_OBJECT_0:
				{
					if (!GetOverlappedResult(_directory, &overlapped_buffer, &bytes_returned, TRUE)) {
						throw std::system_error(GetLastError(), std::system_category());
					}
					async_pending = false;

					if (bytes_returned == 0) {
						break;
					}

					FILE_NOTIFY_INFORMATION *file_information = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(&buffer[0]);
					do
					{
						std::wstring changed_file_w{ file_information->FileName, file_information->FileNameLength / sizeof(file_information->FileName[0]) };
						UnderpinningString changed_file;
						convert_wstring(changed_file_w, changed_file);
						if (pass_filter(changed_file))
						{
							parsed_information.emplace_back(T{ changed_file }, _event_type_mapping.at(file_information->Action));
						}

						if (file_information->NextEntryOffset == 0) {
							break;
						}

						file_information = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<BYTE*>(file_information) + file_information->NextEntryOffset);
					} while (true);
					break;
				}
				case WAIT_OBJECT_0 + 1:
					// quit
					break;
				case WAIT_FAILED:
					break;
				}
				//dispatch callbacks
				{
					std::lock_guard<std::mutex> lock(_callback_mutex);
					_callback_information.insert(_callback_information.end(), parsed_information.begin(), parsed_information.end());
				}
				_cv.notify_all();
			} while (_destory == false);

			if (async_pending)
			{
				//clean up running async io
				CancelIo(_directory);
				GetOverlappedResult(_directory, &overlapped_buffer, &bytes_returned, TRUE);
			}
		}
#endif // WIN32

#if __unix__

		bool is_file(const T& path) const
		{
			struct stat statbuf = {};
			if (stat(path.c_str(), &statbuf) != 0)
			{
				throw std::system_error(errno, std::system_category());
			}
			return S_ISREG(statbuf.st_mode);
		}

		FolderInfo get_directory(const T& path) 
		{
			const auto folder = inotify_init();
			if (folder < 0) 
			{
				throw std::system_error(errno, std::system_category());
			}
			const auto listen_filters = _listen_filters;

			_watching_single_file = is_file(path);

			const T watch_path = [this, &path]() {
				if (_watching_single_file)
				{
					const auto parsed_path = split_directory_and_file(path);
					_filename = parsed_path.filename;
					return parsed_path.directory;
				}
				else
				{
					return path;
				}
			}();

			const auto watch = inotify_add_watch(folder, watch_path.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
			if (watch < 0) 
			{
				throw std::system_error(errno, std::system_category());
			}
			return { folder, watch };
		}

		void monitor_directory() 
		{
			std::vector<char> buffer(_buffer_size);

			_running.set_value();
			while (_destory == false) 
			{
				const auto length = read(_directory.folder, static_cast<void*>(buffer.data()), buffer.size());
				if (length > 0) 
				{
					int i = 0;
					std::vector<std::pair<T, Event>> parsed_information;
					while (i < length) 
					{
						struct inotify_event *event = reinterpret_cast<struct inotify_event *>(&buffer[i]); // NOLINT
						if (event->len) 
						{
							const UnderpinningString changed_file{ event->name };
							if (pass_filter(changed_file))
							{
								if (event->mask & IN_CREATE) 
								{
									parsed_information.emplace_back(T{ changed_file }, Event::added);
								}
								else if (event->mask & IN_DELETE) 
								{
									parsed_information.emplace_back(T{ changed_file }, Event::removed);
								}
								else if (event->mask & IN_MODIFY) 
								{
									parsed_information.emplace_back(T{ changed_file }, Event::modified);
								}
							}
						}
						i += event_size + event->len;
					}
					//dispatch callbacks
					{
						std::lock_guard<std::mutex> lock(_callback_mutex);
						_callback_information.insert(_callback_information.end(), parsed_information.begin(), parsed_information.end());
					}
					_cv.notify_all();
				}
			}
		}
#endif // __unix__

		void callback_thread()
		{
			while (_destory == false) {
				std::unique_lock<std::mutex> lock(_callback_mutex);
				if (_callback_information.empty() && _destory == false) {
					_cv.wait(lock, [this] { return _callback_information.size() > 0 || _destory; });
				}
				decltype(_callback_information) callback_information = {};
				std::swap(callback_information, _callback_information);
				lock.unlock();

				for (const auto& file : callback_information) {
					if (_callback) {
						try
						{
							_callback(file.first, file.second);
						}
						catch (const std::exception&)
						{
						}
					}
				}
			}
		}
	};

	template<class T> constexpr typename FileWatch<T>::C FileWatch<T>::_regex_all[];
	template<class T> constexpr typename FileWatch<T>::C FileWatch<T>::_this_directory[];
}
#endif