#pragma once

namespace Hazel {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void UpdateViewport(unsigned int width, unsigned int height) = 0;
		virtual void SwapBuffers() = 0;
	};

}