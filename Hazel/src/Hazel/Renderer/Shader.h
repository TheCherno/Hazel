#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Hazel {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(std::string_view name, int value) = 0;
		virtual void SetIntArray(std::string_view name, int* values, uint32_t count) = 0;
		virtual void SetFloat(std::string_view name, float value) = 0;
		virtual void SetFloat3(std::string_view name, const glm::vec3& value) = 0;
		virtual void SetFloat4(std::string_view name, const glm::vec4& value) = 0;
		virtual void SetMat4(std::string_view name, const glm::mat4& value) = 0;

		[[nodiscard]] virtual std::string_view GetName() const = 0;

		static Ref<Shader> Create(std::string_view filepath);
		static Ref<Shader> Create(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(std::string_view name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(std::string_view filepath);
		Ref<Shader> Load(std::string_view name, std::string_view filepath);

		Ref<Shader> Get(std::string_view name);

		bool Exists(std::string_view name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}