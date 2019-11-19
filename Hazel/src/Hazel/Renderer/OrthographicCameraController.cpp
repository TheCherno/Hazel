#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_EnableRotation(rotation)
	{
		/* Those remaps can be done (and should be done) at user-level component
		 * (layers or apps). However, since this CameraController is using those
		 * Key Inputs, if user forgot to map those key, camera will not react to 
		 * inputs, so we pre-map at least those keys here.
		 */
		Input::Remap("camera_move_left", Hazel::KeyAlternative(Hazel::Keys::A));
		Input::Remap("camera_move_right", Hazel::KeyAlternative(Hazel::Keys::D));
		Input::Remap("camera_move_up", Hazel::KeyAlternative(Hazel::Keys::W));
		Input::Remap("camera_move_down", Hazel::KeyAlternative(Hazel::Keys::S));

		Input::Remap("camera_rotate_clockwise", Hazel::KeyAlternative(Hazel::Keys::E));
		Input::Remap("camera_rotate_anti_clockwise", Hazel::KeyAlternative(Hazel::Keys::Q));
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HZ_CORE_INFO("Trans: {0}", m_CameraTranslationSpeed);
		if (Input::IsInputPressed("camera_move_left"))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsInputPressed("camera_move_right"))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsInputPressed("camera_move_up"))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsInputPressed("camera_move_down"))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_EnableRotation)
		{
			if (Input::IsInputPressed("camera_rotate_anti_clockwise"))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsInputPressed("camera_rotate_clockwise"))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		//m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::SetZoomLevel(float level) 
	{
		// translation speed should scale relative to the zoom level changes;
		float diff = level / m_ZoomLevel;
		m_CameraTranslationSpeed *= diff;
		m_ZoomLevel = level;
		UpdateProjectionMatrix();
	}

	void OrthographicCameraController::UpdateProjectionMatrix()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		float zoomLevel = m_ZoomLevel - e.GetYOffset() * m_ZoomRate;
		zoomLevel = std::max(zoomLevel, m_MaxZoomLevel);
		zoomLevel = std::min(zoomLevel, m_MinZoomLevel);
		SetZoomLevel(zoomLevel);
		UpdateProjectionMatrix();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		UpdateProjectionMatrix();
		return false;
	}

}