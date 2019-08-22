#include "spdlog/sinks/base_sink.h"
#include "ImGuiConsole.h"

namespace Hazel {

	template<class Mutex>
	class ImGuiConsoleSink : public spdlog::sinks::base_sink<std::mutex>
	{
	public:
		explicit ImGuiConsoleSink(bool forceFlush = false, uint8_t bufferCapacity = 10)
			: m_MessageBufferCapacity(forceFlush ? 1 : bufferCapacity), m_MessageBuffer(std::vector<Ref<ImGuiConsole::Message>>(forceFlush ? 1 : bufferCapacity))
		{
		}
		ImGuiConsoleSink(const ImGuiConsoleSink&) = delete;
		ImGuiConsoleSink& operator=(const ImGuiConsoleSink&) = delete;
		virtual ~ImGuiConsoleSink() = default;
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			fmt::memory_buffer formatted;
			sink::formatter_->format(msg, formatted);

			*(m_MessageBuffer.begin() + m_MessagesBuffered) = std::make_shared<ImGuiConsole::Message>(fmt::to_string(formatted), GetMessageLevel(msg.level));
			if (++m_MessagesBuffered == m_MessageBufferCapacity)
				flush_();
		}

		void flush_() override
		{
			for (Ref<ImGuiConsole::Message> message : m_MessageBuffer)
				ImGuiConsole::AddMessage(message);
			m_MessagesBuffered = 0;
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
	private:
		uint8_t m_MessagesBuffered = 0;
		uint8_t m_MessageBufferCapacity;
		std::vector<Ref<ImGuiConsole::Message>> m_MessageBuffer;
	};

}

#include "spdlog/details/null_mutex.h"
#include <mutex>
namespace Hazel {
	using ImGuiConsoleSink_mt = ImGuiConsoleSink<std::mutex>;                  // multi-threaded
	using ImGuiConsoleSink_st = ImGuiConsoleSink<spdlog::details::null_mutex>; // single threaded
}