#pragma once

#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Hazel {

  class LinuxWindow : public Window
  {
  public:
    LinuxWindow(const WindowProps& props);
    virtual ~LinuxWindow(void);

    void OnUpdate(void) override;

    unsigned int GetWidth(void) const override { return m_Data.Width; }
    unsigned int GetHeight(void) const override { return m_Data.Height; }

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync(void) const override;

    virtual void* GetNativeWindow(void) const { return m_Window; }

  private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown(void);

  private:
    GLFWwindow* m_Window;
    Scope<GraphicsContext> m_Context;

    struct WindowData
    {
      std::string Title;
      unsigned int Width, Height;
      bool VSync;

      EventCallbackFn EventCallback;
    };

    WindowData m_Data;
  };

}
