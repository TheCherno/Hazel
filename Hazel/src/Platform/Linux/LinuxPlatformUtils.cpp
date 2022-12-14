#include "hzpch.h"
#include "Hazel/Utils/PlatformUtils.h"
#include "Hazel/Core/Application.h"
#include "Platform/Linux/LinuxDialogWindow.h"

#include <GLFW/glfw3.h>

namespace Hazel {

  float Time::GetTime(void)
  {
    return glfwGetTime();
  }

  std::string FileDialogs::OpenFile(const char* filter)
  {
    std::string res;
    auto app = Gtk::Application::create("Hazel File Selector");
    LinuxDialogWindow window;
    window.SubmitHazelFilter(filter);
    app->run(window);
    res = window.GetFileName();

    if (!res.empty())
      return res;
    return std::string();
  }

  std::string FileDialogs::SaveFile(const char* filter)
  {
    std::string res;
    auto app = Gtk::Application::create("Hazel File Selector");
    LinuxDialogWindow window;
    window.SubmitHazelFilter(filter);
    app->run(window);
    res = window.GetFileName();

    if (!res.empty())
      return res;
    return std::string();
  }

}
