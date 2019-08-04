#include "hzpch.h"
#include "ImGuiConsole.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Hazel {

	uint16_t ImGuiConsole::s_MessageBufferCapacity = 200;
	std::vector<std::shared_ptr<ImGuiConsole::Message>> ImGuiConsole::s_MessageBuffer(s_MessageBufferCapacity);
	uint16_t ImGuiConsole::s_MessageBufferIndex = 0;
	ImGuiConsole::Message::Level ImGuiConsole::s_MessageBufferRenderFilter = ImGuiConsole::Message::Level::Trace;

	std::shared_ptr<ImGuiConsole> ImGuiConsole::GetConsole()
	{
		return std::dynamic_pointer_cast<ImGuiConsole>(Log::GetSinks()[1]);
	}

	void ImGuiConsole::AddMessage(std::shared_ptr<Message> message)
	{
		if (message->m_Level == Message::Level::Invalid)
			return;

		*(s_MessageBuffer.begin() + s_MessageBufferIndex) = message;
		if (++s_MessageBufferIndex == s_MessageBufferCapacity)
			s_MessageBufferIndex = 0;
	}

	void ImGuiConsole::OnImGuiRender(bool* show)
	{
		ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
		ImGui::Begin("Console", show);
		{
			ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			{
				auto messageStart = s_MessageBuffer.begin() + s_MessageBufferIndex;
				if (*messageStart) // If contains old message here
					for (auto message = messageStart; message != s_MessageBuffer.end(); message++)
						(*message)->OnImGuiRender();
				if (s_MessageBufferIndex != 0) // Skipped first messages in vector
					for (auto message = s_MessageBuffer.begin(); message != messageStart; message++)
						(*message)->OnImGuiRender();
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}

	std::vector<ImGuiConsole::Message::Level> ImGuiConsole::Message::s_Levels{
		ImGuiConsole::Message::Level::Trace,
		//ImGuiConsole::Message::Level::Debug,
		ImGuiConsole::Message::Level::Info,
		ImGuiConsole::Message::Level::Warn,
		ImGuiConsole::Message::Level::Error,
		ImGuiConsole::Message::Level::Critical,
		ImGuiConsole::Message::Level::Off
	};

	ImGuiConsole::Message::Message(const std::string message, Level level)
		: m_Message(message), m_Level(level)
	{
	}

	void ImGuiConsole::Message::OnImGuiRender()
	{
		if (Valid() && m_Level >= ImGuiConsole::s_MessageBufferRenderFilter)
		{
			Color color = GetRenderColor(m_Level);
			ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
			ImGui::TextUnformatted(m_Message.c_str());
			ImGui::PopStyleColor();
		}
	}

	ImGuiConsole::Message::Color ImGuiConsole::Message::GetRenderColor(Level level)
	{
		switch (level)
		{
			case ImGuiConsole::Message::Level::Trace   : return { 0.75f, 0.75f, 0.75f, 1.00f }; // White-ish gray
			case ImGuiConsole::Message::Level::Info    : return { 0.00f, 0.50f, 0.00f, 1.00f }; // Green
			case ImGuiConsole::Message::Level::Debug   : return { 0.00f, 0.50f, 0.50f, 1.00f }; // Cyan
			case ImGuiConsole::Message::Level::Warn    : return { 1.00f, 1.00f, 0.00f, 1.00f }; // Yellow
			case ImGuiConsole::Message::Level::Error   : return { 1.00f, 0.00f, 0.00f, 1.00f }; // Red
			case ImGuiConsole::Message::Level::Critical: return { 1.00f, 1.00f, 1.00f, 1.00f }; // White-white
		}
		return { 1.00f, 1.00f, 1.00f, 1.00f };
	}

	const char* ImGuiConsole::Message::GetLevelName(Level level)
	{
		switch (level)
		{
			case ImGuiConsole::Message::Level::Trace   : return "Trace";
			case ImGuiConsole::Message::Level::Info    : return "Info";
			case ImGuiConsole::Message::Level::Debug   : return "Debug";
			case ImGuiConsole::Message::Level::Warn    : return "Warning";
			case ImGuiConsole::Message::Level::Error   : return "Error";
			case ImGuiConsole::Message::Level::Critical: return "Critical";
			case ImGuiConsole::Message::Level::Off     : return "None";
		}
		return "Unknown name";
	}

}