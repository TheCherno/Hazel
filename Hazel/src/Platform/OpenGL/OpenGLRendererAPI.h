#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

#ifdef HZ_ENABLE_RENDERER_LOG
		static void OpenGLMessageCallback(
			unsigned source,
			unsigned type,
			unsigned id,
			unsigned severity,
			int length,
			const char* message,
			const void* userParam);
#endif
	};


}
