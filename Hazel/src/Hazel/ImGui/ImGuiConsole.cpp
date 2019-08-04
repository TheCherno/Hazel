#include "hzpch.h"
#include "ImGuiConsole.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Hazel {

	uint16_t ImGuiConsole::s_MessageBufferCapacity = 200;
	std::vector<std::shared_ptr<ImGuiConsole::Message>> ImGuiConsole::s_MessageBuffer(s_MessageBufferCapacity);
	uint16_t ImGuiConsole::s_MessageBufferIndex = 0;

	std::unordered_map<ImGuiConsole::Message::Level, ImGuiConsole::Color> ImGuiConsole::s_RenderColors = {
		{ImGuiConsole::Message::Level::Trace   , {0.75f, 0.75f, 0.75f, 1.00f}}, // White-ish gray
		{ImGuiConsole::Message::Level::Info    , {0.00f, 0.50f, 0.00f, 1.00f}}, // Green
		{ImGuiConsole::Message::Level::Debug   , {0.00f, 0.50f, 0.50f, 1.00f}}, // Cyan
		{ImGuiConsole::Message::Level::Warn    , {1.00f, 1.00f, 0.00f, 1.00f}}, // Yellow
		{ImGuiConsole::Message::Level::Error   , {1.00f, 0.00f, 0.00f, 1.00f}}, // Red
		{ImGuiConsole::Message::Level::Critical, {1.00f, 1.00f, 1.00f, 1.00f}}  // White-white
	};

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

	ImGuiConsole::Message::Message(const std::string message, Level level)
		: m_Message(message), m_Level(level)
	{
	}

	void ImGuiConsole::Message::OnImGuiRender()
	{
		if (!Valid()) return;

		Color color = s_RenderColors[m_Level];
		ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
		ImGui::TextUnformatted(m_Message.c_str());
		ImGui::PopStyleColor();
	}

}