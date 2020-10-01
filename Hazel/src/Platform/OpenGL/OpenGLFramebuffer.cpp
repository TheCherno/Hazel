#include "hzpch.h"
#include "OpenGLFramebuffer.h"
#include "OpenGLError.h"

#include <glad/glad.h>

namespace Hazel {

	static const uint32_t s_MaxFramebufferSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		HZ_GLCALL(glDeleteFramebuffers(1, &m_RendererID));
		HZ_GLCALL(glDeleteTextures(1, &m_ColorAttachment));
		HZ_GLCALL(glDeleteTextures(1, &m_DepthAttachment));
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			HZ_GLCALL(glDeleteFramebuffers(1, &m_RendererID));
			HZ_GLCALL(glDeleteTextures(1, &m_ColorAttachment));
			HZ_GLCALL(glDeleteTextures(1, &m_DepthAttachment));
		}

		HZ_GLCALL(glCreateFramebuffers(1, &m_RendererID));
		HZ_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
		
		HZ_GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment));
		HZ_GLCALL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment));
		HZ_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		HZ_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		HZ_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		HZ_GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0));

		HZ_GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment));
		HZ_GLCALL(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
		HZ_GLCALL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height));
		HZ_GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0));

		HZ_GLCALL(GLenum framebufferComplete = glCheckFramebufferStatus(GL_FRAMEBUFFER));
		HZ_CORE_ASSERT(framebufferComplete == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		HZ_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Bind()
	{
		HZ_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
		HZ_GLCALL(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	}

	void OpenGLFramebuffer::Unbind()
	{
		HZ_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			HZ_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		
		Invalidate();
	}

}
