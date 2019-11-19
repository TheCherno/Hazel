#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		/* Currently SetZoomLevel can override MaxZoomLevel and MinZoomLevel. Currently. */
		void SetZoomLevel(float level);

		bool IsRotationEnabled() const { return m_EnableRotation; }
		void SetEnableRotation(bool enabled) { m_EnableRotation = enabled; }
	private:
		void UpdateProjectionMatrix();
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		OrthographicCamera m_Camera;

		bool m_EnableRotation;

		// TODO: add helper function to get/set those values, or public them;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
		float m_ZoomRate = 0.25f;
		float m_MaxZoomLevel = 0.25f;
		float m_MinZoomLevel = 2.0f;
	};

}