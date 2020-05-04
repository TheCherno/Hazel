#pragma once

#include "Hazel/Renderer/Texture.h"

#include <glad/glad.h>

namespace Hazel {

	class OpenGLTexture2D : public Texture2D
	{
	public:
        explicit OpenGLTexture2D(uint32_t width, uint32_t height);
        explicit OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		[[nodiscard]] uint32_t GetWidth() const override { return m_Width;  }
		[[nodiscard]] uint32_t GetHeight() const override { return m_Height; }
		
		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) const override;

		bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};

}
