#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float_t left, float_t right, float_t bottom, float_t top);

		void SetProjection(float_t left, float_t right, float_t bottom, float_t top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float_t GetRotation() const { return m_Rotation; }
		void SetRotation(float_t rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float_t m_Rotation = 0.0f;
	};

}
