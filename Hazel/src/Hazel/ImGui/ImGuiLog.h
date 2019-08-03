#include "spdlog/sinks/base_sink.h"

namespace Hazel {

    template<class Mutex>
    class ImGuiLog : public spdlog::sinks::base_sink<std::mutex> {
    public:
        explicit ImGuiLog() {}
        ImGuiLog(const ImGuiLog&) = delete;
        ImGuiLog& operator=(const ImGuiLog&) = delete;
        virtual ~ImGuiLog() = default;

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            // log_msg is a struct containing the log entry info like level, timestamp, thread id etc.
            // msg.raw contains pre formatted log

            // If needed (very likely but not mandatory), the sink formats the message before sending it to its final destination:
            fmt::memory_buffer formatted;
            sink::formatter_->format(msg, formatted);
            std::cout << fmt::to_string(formatted);
        }

        void flush_() override
        {
            std::cout << std::flush;
        }
    };

}

#include "spdlog/details/null_mutex.h"
#include <mutex>
namespace Hazel {
    using ImGuiLog_mt = ImGuiLog<std::mutex>;                  // multi-threaded
    using ImGuiLog_st = ImGuiLog<spdlog::details::null_mutex>; // single threaded
}