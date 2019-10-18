#include "hzpch.h"
#include "RenderCommand.h"

namespace Hazel {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}