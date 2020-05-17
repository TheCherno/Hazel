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
		
		const float dTranslation = m_CameraTranslationSpeed * ts;
		const float dCos = dTranslation * cos(glm::radians(m_CameraRotation));
		const float dSin = dTranslation * sin(glm::radians(m_CameraRotation));

		if (Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraPosition.x -= dCos;
			m_CameraPosition.y -= dSin;
		}
		if (Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraPosition.x += dCos;
			m_CameraPosition.y += dSin;
		}
		if (Input::IsKeyPressed(HZ_KEY_W))
		{
			m_CameraPosition.x += dSin;
			m_CameraPosition.y += dCos;
		}
		if (Input::IsKeyPressed(HZ_KEY_S))
		{
			m_CameraPosition.x -= dSin;
			m_CameraPosition.y -= dCos;
		}
		m_Camera.SetPosition(m_CameraPosition);

		if (m_Rotation)
		{
			const float dRotation = m_CameraRotationSpeed * ts;

			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_CameraRotation += dRotation;
			if (Input::IsKeyPressed(HZ_KEY_E))
				m_CameraRotation -= dRotation;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

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
	
}
