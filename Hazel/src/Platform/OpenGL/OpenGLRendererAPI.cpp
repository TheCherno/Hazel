#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hazel {
#ifdef HZ_ENABLE_RENDERER_LOG
	void OpenGLRendererAPI::OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:			HZ_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:			HZ_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:				HZ_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION:	HZ_CORE_TRACE(message); return;
		}
	}
#endif

	void OpenGLRendererAPI::Init()
	{
#ifdef HZ_ENABLE_RENDERER_LOG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}