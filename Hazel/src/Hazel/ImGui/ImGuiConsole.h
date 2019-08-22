#pragma once

#include "Hazel\Core.h"

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
		private:
			struct Color { float r, g, b, a; };
		public:
			Message(const std::string message = "", Level level = Level::Invalid);
			void OnImGuiRender();

			static Level GetLowerLevel(Level level);
			static Level GetHigherLevel(Level level);
			static const char* GetLevelName(Level level);
		private:
			static Color GetRenderColor(Level level);
		public:
			const std::string m_Message;
			const Level m_Level;
			static std::vector<Level> s_Levels;
		};
	public:
		~ImGuiConsole() = default;
		static void AddMessage(Ref<Message> message);
		static void Clear();
		static void OnImGuiRender(bool* show);
	protected:
		ImGuiConsole() = default;
	private:
		struct ImGuiRendering
		{
			static void ImGuiRenderHeader();
			static void ImGuiRenderMessages();
		};
	private:
		static uint16_t s_MessageBufferCapacity;
		static uint16_t s_MessageBufferSize;
		static uint16_t s_MessageBufferBegin;
		static Message::Level s_MessageBufferRenderFilter;
		static std::vector<Ref<Message>> s_MessageBuffer;
		static bool s_AllowScrollingToBottom;
		static bool s_RequestScrollToBottom;
	};

}
