#pragma once

#include "Hazel/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Hazel {

	class OpenGLShader : public Shader
	{
	public:
		explicit OpenGLShader(std::string_view filepath);
		OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(std::string_view name, int value) override;
		void SetIntArray(std::string_view name, int* values, uint32_t count) override;
		void SetFloat(std::string_view name, float value) override;
		void SetFloat3(std::string_view name, const glm::vec3& value) override;
		void SetFloat4(std::string_view name, const glm::vec4& value) override;
		void SetMat4(std::string_view name, const glm::mat4& value) override;

		[[nodiscard]] std::string_view GetName() const override { return m_Name; }

		void UploadUniformInt(std::string_view name, int value) const;
		void UploadUniformIntArray(std::string_view name, int* values, uint32_t count) const;

		void UploadUniformFloat(std::string_view name, float value) const;
		void UploadUniformFloat2(std::string_view name, const glm::vec2& value) const;
		void UploadUniformFloat3(std::string_view name, const glm::vec3& value) const;
		void UploadUniformFloat4(std::string_view name, const glm::vec4& value) const;

		void UploadUniformMat3(std::string_view name, const glm::mat3& matrix) const;
		void UploadUniformMat4(std::string_view name, const glm::mat4& matrix) const;
	private:
		std::string ReadFile(std::string_view filepath);
		std::unordered_map<GLenum, std::string> PreProcess(std::string_view source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}