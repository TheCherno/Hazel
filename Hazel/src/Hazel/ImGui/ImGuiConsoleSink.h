#include "spdlog/sinks/base_sink.h"
#include "ImGuiConsole.h"

namespace Hazel {

	template<class Mutex>
	class ImGuiConsoleSink : public spdlog::sinks::base_sink<std::mutex>
	{
	public:
		explicit ImGuiConsoleSink() = default;
		ImGuiConsoleSink(const ImGuiConsoleSink&) = delete;
		ImGuiConsoleSink& operator=(const ImGuiConsoleSink&) = delete;
		virtual ~ImGuiConsoleSink() = default;
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			fmt::memory_buffer formatted;
			sink::formatter_->format(msg, formatted);
			ImGuiConsole::AddMessage(std::make_shared<ImGuiConsole::Message>(fmt::to_string(formatted), GetMessageLevel(msg.level)));
		}

		void flush_() override
		{
		}
	private:
		static ImGuiConsole::Message::Level GetMessageLevel(const spdlog::level::level_enum level)
		{
			switch (level)
			{
				case spdlog::level::level_enum::trace   : return ImGuiConsole::Message::Level::Trace;
				case spdlog::level::level_enum::debug   : return ImGuiConsole::Message::Level::Debug;
				case spdlog::level::level_enum::info    : return ImGuiConsole::Message::Level::Info;
				case spdlog::level::level_enum::warn    : return ImGuiConsole::Message::Level::Warn;
				case spdlog::level::level_enum::err     : return ImGuiConsole::Message::Level::Error;
				case spdlog::level::level_enum::critical: return ImGuiConsole::Message::Level::Critical;
				case spdlog::level::level_enum::off     : return ImGuiConsole::Message::Level::Off;
			}
			return ImGuiConsole::Message::Level::Invalid;
		}
	};

}

#include "spdlog/details/null_mutex.h"
#include <mutex>
namespace Hazel {
	using ImGuiConsoleSink_mt = ImGuiConsoleSink<std::mutex>;                  // multi-threaded
	using ImGuiConsoleSink_st = ImGuiConsoleSink<spdlog::details::null_mutex>; // single threaded
}