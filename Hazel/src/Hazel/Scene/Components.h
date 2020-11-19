#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SceneCamera.h"
#include "ScriptableEntity.h"

namespace Hazel {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform()
		{
			bool isDirty = false;
			if (Translation.x != m_TransformationMatrix[3].x
				|| Translation.y != m_TransformationMatrix[3].y
				|| Translation.z != m_TransformationMatrix[3].z)
			{
				isDirty = true;
			}
			if (Rotation != m_PreviousRotation)
			{
				isDirty = true;
				m_PreviousRotation = Rotation;
			}
			if (Scale != m_PreviousScale)
			{
				isDirty = true;
				m_PreviousScale = Scale;
			}

			if (isDirty)
			{
				//HZ_CORE_DEBUG("Transformation component changes detected. Recalculating Transformation Matrix...");
				m_TransformationMatrix = glm::translate(glm::mat4(1.0f), Translation)
					* glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
					* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
					* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 })
					* glm::scale(glm::mat4(1.0f), Scale);
			}

			return m_TransformationMatrix;
		}
	private:
		glm::vec3 m_PreviousRotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_PreviousScale = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_TransformationMatrix;
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

}
