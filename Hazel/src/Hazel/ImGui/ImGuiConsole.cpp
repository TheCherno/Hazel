#include "hzpch.h"
#include "ImGuiConsole.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Hazel {

	uint16_t ImGuiConsole::s_MessageBufferCapacity = 200;
	uint16_t ImGuiConsole::s_MessageBufferSize = 0;
	uint16_t ImGuiConsole::s_MessageBufferBegin = 0;
	ImGuiConsole::Message::Level ImGuiConsole::s_MessageBufferRenderFilter = ImGuiConsole::Message::Level::Trace;
	std::vector<std::shared_ptr<ImGuiConsole::Message>> ImGuiConsole::s_MessageBuffer(s_MessageBufferCapacity);
	bool ImGuiConsole::s_AllowScrollingToBottom = true;
	bool ImGuiConsole::s_RequestScrollToBottom = false;

	std::shared_ptr<ImGuiConsole> ImGuiConsole::GetConsole()
	{
		return std::dynamic_pointer_cast<ImGuiConsole>(Log::GetSinks()[1]);
	}

	void ImGuiConsole::AddMessage(std::shared_ptr<Message> message)
	{
		if (message->m_Level == Message::Level::Invalid)
			return;

		*(s_MessageBuffer.begin() + s_MessageBufferBegin) = message;
		if (++s_MessageBufferBegin == s_MessageBufferCapacity)
			s_MessageBufferBegin = 0;
		if (s_MessageBufferSize < s_MessageBufferCapacity)
			s_MessageBufferSize++;

		if (s_AllowScrollingToBottom)
			s_RequestScrollToBottom = true;
	}

	void ImGuiConsole::OnImGuiRender(bool* show)
	{
		ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
		ImGui::Begin("Console", show);
		{
			ImGuiRendering::ImGuiRenderHeader();
			ImGui::Separator();
			ImGuiRendering::ImGuiRenderMessages();
		}
		ImGui::End();
	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderHeader()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		float spacing = style.ItemInnerSpacing.x;
		float button_sz = ImGui::GetFrameHeight();
		float width = ImGui::CalcItemWidth() / 2.0f;

		// Dropdown with levels
		ImGui::PushItemWidth(width - spacing * 2.0f - button_sz * 2.0f);
		if (ImGui::BeginCombo(
			"##MessageBufferRenderFilter",
			Message::GetLevelName(s_MessageBufferRenderFilter),
			ImGuiComboFlags_NoArrowButton))
		{
			for (auto level = Message::s_Levels.begin(); level != Message::s_Levels.end(); level++)
			{
				bool is_selected = (s_MessageBufferRenderFilter == *level);
				if (ImGui::Selectable(Message::GetLevelName(*level), is_selected))
					s_MessageBufferRenderFilter = *level;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		// Buttons to quickly change level
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##MessageBufferRenderFilter_L", ImGuiDir_Left))
		{
			s_MessageBufferRenderFilter = Message::GetLowerLevel(s_MessageBufferRenderFilter);
		}
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##MessageBufferRenderFilter_R", ImGuiDir_Right))
		{
			s_MessageBufferRenderFilter = Message::GetHigherLevel(s_MessageBufferRenderFilter);
		}

		// Text change level
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text("Display level");

		// Checkbox for scrolling lock
		ImGui::SameLine(0.0f, 5.0f * spacing);
		ImGui::Checkbox("Scroll to bottom", &s_AllowScrollingToBottom);
	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderMessages()
	{
		ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			auto messageStart = s_MessageBuffer.begin() + s_MessageBufferBegin;
			if (*messageStart) // If contains old message here
				for (auto message = messageStart; message != s_MessageBuffer.end(); message++)
					(*message)->OnImGuiRender();
			if (s_MessageBufferBegin != 0) // Skipped first messages in vector
				for (auto message = s_MessageBuffer.begin(); message != messageStart; message++)
					(*message)->OnImGuiRender();

			if (s_RequestScrollToBottom && ImGui::GetScrollMaxY() > 0)
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
				s_RequestScrollToBottom = false;
			}
		}
		ImGui::EndChild();
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
		if (m_Level != Level::Invalid && m_Level >= ImGuiConsole::s_MessageBufferRenderFilter)
		{
			Color color = GetRenderColor(m_Level);
			ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
			ImGui::TextUnformatted(m_Message.c_str());
			ImGui::PopStyleColor();
		}
	}

	ImGuiConsole::Message::Level ImGuiConsole::Message::GetLowerLevel(Level level)
	{
		switch (level)
		{
			case ImGuiConsole::Message::Level::Off     : return ImGuiConsole::Message::Level::Critical;
			case ImGuiConsole::Message::Level::Critical: return ImGuiConsole::Message::Level::Error;
			case ImGuiConsole::Message::Level::Error   : return ImGuiConsole::Message::Level::Warn;
			case ImGuiConsole::Message::Level::Warn    : //return ImGuiConsole::Message::Level::Debug;
			case ImGuiConsole::Message::Level::Debug   : return ImGuiConsole::Message::Level::Info;
			case ImGuiConsole::Message::Level::Info    :
			case ImGuiConsole::Message::Level::Trace   : return ImGuiConsole::Message::Level::Trace;
		}
		return ImGuiConsole::Message::Level::Invalid;
	}

	ImGuiConsole::Message::Level ImGuiConsole::Message::GetHigherLevel(Level level)
	{
		switch (level)
		{
			case ImGuiConsole::Message::Level::Trace   : return ImGuiConsole::Message::Level::Info;
			case ImGuiConsole::Message::Level::Info    : //return ImGuiConsole::Message::Level::Debug;
			case ImGuiConsole::Message::Level::Debug   : return ImGuiConsole::Message::Level::Warn;
			case ImGuiConsole::Message::Level::Warn    : return ImGuiConsole::Message::Level::Error;
			case ImGuiConsole::Message::Level::Error   : return ImGuiConsole::Message::Level::Critical;
			case ImGuiConsole::Message::Level::Critical:
			case ImGuiConsole::Message::Level::Off     : return ImGuiConsole::Message::Level::Off;
		}
		return ImGuiConsole::Message::Level::Invalid;
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
}