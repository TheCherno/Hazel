#include "hzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

	Hazel::Scope<RendererAPI> RenderCommand::s_RendererAPI(new OpenGLRendererAPI);

}