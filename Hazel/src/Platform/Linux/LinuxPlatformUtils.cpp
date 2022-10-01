#ifndef HZ_PLATFORM_LINUX
	#ifndef __linux
		#warn "Compiler reports that the current compilation target isn't Linux. This file should be excluded from a compilation target that isn't Linux, UNIX, or POSIX."
	#endif
	#error "HZ_PLATFORM_LINUX is not defined. Linux or a POSIX system is required to compile this file. Please define macro before compiling!"
#endif

#include "hzpch.h"
#include "Hazel/Utils/PlatformUtils.h"

#include <GLFW/glfw3.h>
#include "Hazel/Core/Application.h"

#define LINUX_PATH_MAX 4096 + 255 + 1

namespace Hazel {

	bool FileDialogsUtilityCheck();

	std::string FileDialogs::OpenFile(const char* filter)
	{
		if (!FileDialogsUtilityCheck())
			return std::string();

		const char* file_extension = std::strchr(filter, 0) + 1;

		FILE *fp;
		char path[LINUX_PATH_MAX];

		std::string cmdline = std::string("zenity --file-selection --file-filter=\"") +
			std::string(file_extension) + std::string("\" --title=\"Open File\"");
		fp = popen(cmdline.c_str(), "r");
		if (fp == NULL)
			HZ_CORE_ERROR("Null file pointer in FileDialogs::OpenFile().\n");

		//Check for File dialog cancellation.
		if (fgets(path, LINUX_PATH_MAX, fp) == NULL)
		{
			pclose(fp);
			return std::string();
		}

		pclose(fp);

		std::string file_choice = std::string(path);
		int endline_pos = file_choice.find_first_of("\n");
		file_choice.resize(endline_pos);
		return file_choice;
	}

	std::string FileDialogs::SaveFile(const char* filter)
	{
		if (!FileDialogsUtilityCheck())
			return std::string();

		FILE *fp;
		char path[LINUX_PATH_MAX];
		const char* file_extension = std::strchr(filter, 0) + 1;
		std::string shortened_ext(file_extension);
		shortened_ext.erase(0,1);

		std::string cmdline = std::string("zenity --file-selection --file-filter=\"") +
			std::string(file_extension) + std::string("\" --filename=\"") + shortened_ext
			+ ("\" --title=\"Save As File\" --save --confirm-overwrite");
		fp = popen(cmdline.c_str(), "r");
		if (fp == NULL)
			HZ_CORE_ERROR("Null file pointer in FileDialogs::OpenFile().\n");

		//Check for File dialog cancellation.
		if (fgets(path, LINUX_PATH_MAX, fp) == NULL)
		{
			pclose(fp);
			return std::string();
		}

		pclose(fp);

		std::string file_choice = std::string(path);
		int endline_pos = file_choice.find_first_of("\n");
		file_choice.resize(endline_pos);
		return file_choice;
	}

	bool FileDialogsUtilityCheck()
	{
		FILE *fp;
		char path[LINUX_PATH_MAX];

		fp = popen("which zenity", "r");
		if (fp == NULL)
			HZ_CORE_ERROR("Null file pointer in FileDialogs::OpenFile().\n");

		if (fgets(path, LINUX_PATH_MAX, fp) == NULL)
		{
			HZ_CORE_WARN("Zenity not found in path. See Hazel pre-requisites to install.");
			pclose(fp);
			return false;
		}
		pclose(fp);

		return true;
	}

	float Time::GetTime()
	{
		return glfwGetTime();
	}
}
