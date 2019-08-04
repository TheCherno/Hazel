#pragma once

namespace Hazel {

    class ImGuiConsole
    {
    public:
        struct Message
        {
        public:
            enum class Level : int8_t
            {
                Invalid = -1,
                Trace = 0,
                Info = 1,
                Warn = 2,
                Error = 3,
                Critical = 4,
                None = 5,
            };
        public:
            Message(const char* msg = "", Level lvl = Level::Invalid);
            inline bool Valid() { return m_Level != Level::Invalid; }
        public:
            const char* m_Message;
            Level m_Level;
        };
    public:
        ~ImGuiConsole() = default;
        static void OnImGuiRender(bool* show);
    protected:
        ImGuiConsole();
        static void AddMessage(Message msg);
    private:
        static uint16_t s_MessageBufferCapacity;
        static std::vector<Message> s_MessageBuffer;
        static uint16_t s_MessageBufferIndex;
    };

}
