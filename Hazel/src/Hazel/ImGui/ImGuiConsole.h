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
                Debug = 1,
                Info = 2,
                Warn = 3,
                Error = 4,
                Critical = 5,
                Off = 6, // Display nothing
            };
        public:
            Message(const std::string message = "", Level level = Level::Invalid);
            inline bool Valid() { return m_Level != Level::Invalid; }
            void OnImGuiRender();
        public:
            const std::string m_Message;
            const Level m_Level;
        };
        struct Color { float r, g, b, a; };
    public:
        ~ImGuiConsole() = default;
        static std::shared_ptr<ImGuiConsole> GetConsole();
        static void OnImGuiRender(bool* show);
        static inline void SetColor(Message::Level level, Color color) { s_RenderColors[level] = color; }
    protected:
        ImGuiConsole() = default;
        static void AddMessage(std::shared_ptr<Message> message);
    private:
        static uint16_t s_MessageBufferCapacity;
        static std::vector<std::shared_ptr<Message>> s_MessageBuffer;
        static uint16_t s_MessageBufferIndex;
        static std::unordered_map<Message::Level, Color> s_RenderColors;
    };

}
