#include "hzpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "OpenGLError.h"

#include <glad/glad.h>

namespace Hazel {
	
	void OpenGLMessageCallback(
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
			case GL_DEBUG_SEVERITY_HIGH:         HZ_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       HZ_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          HZ_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: HZ_CORE_TRACE(message); return;
		}
		
		HZ_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		HZ_PROFILE_FUNCTION();

	#ifdef HZ_DEBUG
		HZ_GLCALL(glEnable(GL_DEBUG_OUTPUT));
		HZ_GLCALL(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
		HZ_GLCALL(glDebugMessageCallback(OpenGLMessageCallback, nullptr));
		
		HZ_GLCALL(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE));
	#endif

		HZ_GLCALL(glEnable(GL_BLEND));
		HZ_GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		HZ_GLCALL(glEnable(GL_DEPTH_TEST));
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		HZ_GLCALL(glViewport(x, y, width, height));
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		HZ_GLCALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRendererAPI::Clear()
	{
		HZ_GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		HZ_GLCALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
		HZ_GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

}
