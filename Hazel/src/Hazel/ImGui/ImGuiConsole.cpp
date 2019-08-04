#include "hzpch.h"
#include "ImGuiConsole.h"

#include "imgui.h"

namespace Hazel {

    uint16_t ImGuiConsole::s_MessageBufferCapacity = 200;
    std::vector<ImGuiConsole::Message> ImGuiConsole::s_MessageBuffer(s_MessageBufferCapacity);
    uint16_t ImGuiConsole::s_MessageBufferIndex = 0;

    ImGuiConsole::ImGuiConsole()
    {
        std::cout << "Test\n";
    }

    void ImGuiConsole::AddMessage(Message msg)
    {
        if (msg.m_Level == Message::Level::Invalid)
            return;

        std::cout << "Added Message at " << s_MessageBufferIndex << "\n";
        *(s_MessageBuffer.begin() + s_MessageBufferIndex) = msg;

        if (++s_MessageBufferIndex == s_MessageBufferCapacity)
            s_MessageBufferIndex = 0;
    }

    void ImGuiConsole::OnImGuiRender(bool* show)
    {
        std::cout << "Rendering console\n";

        ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
        ImGui::Begin("Console", show);
        {
            auto messageStart = s_MessageBuffer.begin() + s_MessageBufferIndex;
            if (messageStart->Valid()) // If contains old message here
                for (auto it = messageStart; it != s_MessageBuffer.end(); it++)
                    std::cout << "Rendering message\n";
            if (s_MessageBufferIndex != 0) // Skipped first messages in vector
                for (auto it = s_MessageBuffer.begin(); it != messageStart; it++)
                    std::cout << "Rendering message\n";
        }
        ImGui::End();
    }

    ImGuiConsole::Message::Message(const char* msg, Level lvl)
        : m_Message(msg), m_Level(lvl)
    {
    }

}