#pragma once

#include "Hazel/Renderer/Shader.h"
#include <string>

namespace Hazel {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        unsigned int CompileShader(const char* shaderSrc, uint32_t shaderType);

    private:
        uint32_t m_RendererID;
        std::string m_VertexShaderSource;
        std::string m_FragmentShaderSource;
    };

}