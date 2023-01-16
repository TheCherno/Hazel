#include "hzpch.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel {

  bool Input::IsKeyPressed(const KeyCode key)
  {
    auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS;
  }

  bool Input::IsMouseButtonPressed(const MouseCode button)
  {
    auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
  }

  glm::vec2 Input::GetMousePosition(void)
  {
    auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
  }

  float Input::GetMouseX(void)
  {
    return GetMousePosition().x;
  }

  float Input::GetMouseY(void)
  {
    return GetMousePosition().y;
  }

}
