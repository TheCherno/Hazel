#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HZ_PROFILE_FUNCTION();
		
		float dTranslationSpeed = m_CameraTranslationSpeed * ts;
		float dRotationSpeed    = m_CameraRotationSpeed * ts;
		float theta = m_CameraRotation;
		float dX = cos(glm::radians(theta));
		float dY = sin(glm::radians(theta));

		if (Input::IsKeyPressed(HZ_KEY_A)) ChangePosition(-(dX * dTranslationSpeed), -(dY * dTranslationSpeed));
		if (Input::IsKeyPressed(HZ_KEY_D)) ChangePosition(dX * dTranslationSpeed, dY * dTranslationSpeed);
		if (Input::IsKeyPressed(HZ_KEY_W)) ChangePosition(-dY * dTranslationSpeed, dX * dTranslationSpeed);
		if (Input::IsKeyPressed(HZ_KEY_S)) ChangePosition(-(-dY * dTranslationSpeed), -(dX * dTranslationSpeed));
		
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HZ_KEY_Q)) ChangeRotation(-dRotationSpeed);
			if (Input::IsKeyPressed(HZ_KEY_E)) ChangeRotation(dRotationSpeed);

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	
	void OrthographicCameraController::ChangePosition(float deltaX, float deltaY)
	{ 
		m_CameraPosition.x += deltaX;
		m_CameraPosition.y += deltaY;

		m_Camera.SetPosition(m_CameraPosition);
	}
		
	void OrthographicCameraController::ChangeRotation(float rotation) 
	{ 
		m_CameraRotation += rotation;

		m_Camera.SetRotation(m_CameraRotation);
	}

}
