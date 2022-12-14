#include "hzpch.h"
#include "Hazel/Renderer/RenderCommand.h"

namespace Hazel {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}