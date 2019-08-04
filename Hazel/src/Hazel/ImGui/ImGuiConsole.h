#pragma once

namespace Hazel {

	class ImGuiConsole
	{
	public:
		class Message
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
			struct Color { float r, g, b, a; };
		public:
			Message(const std::string message = "", Level level = Level::Invalid);
			inline bool Valid() { return m_Level != Level::Invalid; }
			void OnImGuiRender();
		private:
			static Color GetRenderColor(Level level);
			static const char* GetLevelName(Level level);
		public:
			const std::string m_Message;
			const Level m_Level;
			static std::vector<Message::Level> s_Levels;
		};
	public:
		~ImGuiConsole() = default;
		static std::shared_ptr<ImGuiConsole> GetConsole();
		static void OnImGuiRender(bool* show);
	protected:
		ImGuiConsole() = default;
		static void AddMessage(std::shared_ptr<Message> message);
	private:
		static uint16_t s_MessageBufferCapacity;
		static std::vector<std::shared_ptr<Message>> s_MessageBuffer;
		static uint16_t s_MessageBufferIndex;
		static Message::Level s_MessageBufferRenderFilter;
	};

}
