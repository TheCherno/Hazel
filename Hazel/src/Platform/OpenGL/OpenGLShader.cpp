#include "hzpch.h"
#include "OpenGLShader.h"

#include <glad\glad.h>

namespace Hazel
{
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_VertexShaderSource(vertexSrc), m_FragmentShaderSource(fragmentSrc)
    {
        //HZ_CORE_INFO("Compiling Vertex Shader...");
        GLuint vertexShader = CompileShader(vertexSrc.c_str(), GL_VERTEX_SHADER);
        if (vertexShader < 1) return;

        //HZ_CORE_INFO("Compiling Fragment Shader...");
        GLuint fragmentShader = CompileShader(fragmentSrc.c_str(), GL_FRAGMENT_SHADER);
        if (fragmentShader < 1) return;

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_RendererID = glCreateProgram();
        GLuint program = m_RendererID;

        // Attach our shaders to our program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            HZ_CORE_ERROR("{0}", infoLog.data());
            HZ_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    unsigned int OpenGLShader::CompileShader(const char* shaderSrc, uint32_t shaderType)
    {
        bool valid =
            (shaderType == GL_VERTEX_SHADER) ||
            (shaderType == GL_FRAGMENT_SHADER);

        HZ_CORE_ASSERT(valid, "Unknown Shader type!");

        // Create an empty shader handle
        GLuint shader = glCreateShader(shaderType);

        // Send the shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        glShaderSource(shader, 1, &shaderSrc, 0);

        // Compile the shader
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(shader);

            HZ_CORE_ERROR("{0}", infoLog.data());
            HZ_CORE_ASSERT(false, "Shader compilation failure!");
            return -1;
        }

        return shader;
    }
}
