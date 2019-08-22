#include "hzpch.h"
#include "ImGuiConsole.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Hazel {

	float ImGuiConsole::s_DisplayScale = 1.0f;
	uint16_t ImGuiConsole::s_MessageBufferCapacity = 200;
	uint16_t ImGuiConsole::s_MessageBufferSize = 0;
	uint16_t ImGuiConsole::s_MessageBufferBegin = 0;
	ImGuiConsole::Message::Level ImGuiConsole::s_MessageBufferRenderFilter = ImGuiConsole::Message::Level::Trace;
	std::vector<Ref<ImGuiConsole::Message>> ImGuiConsole::s_MessageBuffer(s_MessageBufferCapacity);
	bool ImGuiConsole::s_AllowScrollingToBottom = true;
	bool ImGuiConsole::s_RequestScrollToBottom = false;

	void ImGuiConsole::AddMessage(Ref<Message> message)
	{
		if (message->m_Level == Message::Level::Invalid)
			return;

		*(s_MessageBuffer.begin() + s_MessageBufferBegin) = message;
		if (++s_MessageBufferBegin == s_MessageBufferCapacity)
			s_MessageBufferBegin = 0;
		if (s_MessageBufferSize < s_MessageBufferCapacity)
			s_MessageBufferSize++;

		// Request to scroll to bottom of the list to view the new message
		s_RequestScrollToBottom = s_AllowScrollingToBottom;
	}

	void ImGuiConsole::Clear()
	{
		for (auto message = s_MessageBuffer.begin(); message != s_MessageBuffer.end(); message++)
			(*message) = std::make_shared<Message>();
		s_MessageBufferBegin = 0;
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
		const float spacing = style.ItemInnerSpacing.x;

		// Text change level
		ImGui::AlignFirstTextHeightToWidgets();
		ImGui::Text("Display");

		ImGui::SameLine(0.0f, 2.0f * spacing);

		// Buttons to quickly change level left
		if (ImGui::ArrowButton("##MessageRenderFilter_L", ImGuiDir_Left))
		{
			s_MessageBufferRenderFilter = Message::GetLowerLevel(s_MessageBufferRenderFilter);
		}

		ImGui::SameLine(0.0f, spacing);

		// Dropdown with levels
		ImGui::PushItemWidth(ImGui::CalcTextSize("Critical").x * 1.36f);
		if (ImGui::BeginCombo(
			"##MessageRenderFilter",
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

		ImGui::SameLine(0.0f, spacing);

		// Buttons to quickly change level right
		if (ImGui::ArrowButton("##MessageRenderFilter_R", ImGuiDir_Right))
		{
			s_MessageBufferRenderFilter = Message::GetHigherLevel(s_MessageBufferRenderFilter);
		}

		ImGui::SameLine(0.0f, spacing);

		// Button for advanced settings
		ImGui::SameLine(0.0f, ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Settings").x - style.WindowPadding.x / 2.0f);
		if (ImGui::Button("Settings"))
			ImGui::OpenPopup("SettingsPopup");
		if (ImGui::BeginPopup("SettingsPopup"))
		{
			ImGuiRenderSettings();
			ImGui::EndPopup();
		}

	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderSettings()
	{
		const float maxWidth = ImGui::CalcTextSize("Scroll to bottom").x * 1.1f;
		const float spacing = ImGui::GetStyle().ItemInnerSpacing.x + ImGui::CalcTextSize(" ").x;

		// Checkbox for scrolling lock
		ImGui::AlignFirstTextHeightToWidgets();
		ImGui::Text("Scroll to bottom");
		ImGui::SameLine(0.0f, spacing + maxWidth - ImGui::CalcTextSize("Scroll to bottom").x);
		ImGui::Checkbox("##ScrollToBottom", &s_AllowScrollingToBottom);

		ImGui::SameLine(0.0f, spacing);

		// Button to clear the console
		ImGui::SameLine(0.0f, ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Clear console").x + 1.0f);
		if (ImGui::Button("Clear console"))
			ImGuiConsole::Clear();

		// Slider for font scale
		ImGui::AlignFirstTextHeightToWidgets();
		ImGui::Text("Display scale");
		ImGui::SameLine(0.0f, spacing + maxWidth - ImGui::CalcTextSize("Display scale").x);
		ImGui::PushItemWidth(maxWidth * 1.25f / 1.1f);
		ImGui::SliderFloat("##DisplayScale", &s_DisplayScale, 0.5f, 4.0f, "%.1f");
		ImGui::PopItemWidth();
	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderMessages()
	{

		ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImGui::SetWindowFontScale(s_DisplayScale);

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