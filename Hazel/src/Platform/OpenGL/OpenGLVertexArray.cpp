#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>


namespace Hazel {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Hazel::ShaderDataType::Float:    return GL_FLOAT;
			case Hazel::ShaderDataType::Float2:   return GL_FLOAT;
			case Hazel::ShaderDataType::Float3:   return GL_FLOAT;
			case Hazel::ShaderDataType::Float4:   return GL_FLOAT;
			case Hazel::ShaderDataType::Mat3:     return GL_FLOAT;
			case Hazel::ShaderDataType::Mat4:     return GL_FLOAT;
			case Hazel::ShaderDataType::Int:      return GL_INT;
			case Hazel::ShaderDataType::Int2:     return GL_INT;
			case Hazel::ShaderDataType::Int3:     return GL_INT;
			case Hazel::ShaderDataType::Int4:     return GL_INT;
			case Hazel::ShaderDataType::Bool:     return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		//glBindVertexArray(m_RendererID);
		//vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			//glEnableVertexAttribArray(m_VertexBufferIndex);
			//glVertexAttribPointer(m_VertexBufferIndex,
			//	element.GetComponentCount(),
			//	ShaderDataTypeToOpenGLBaseType(element.Type),
			//	element.Normalized ? GL_TRUE : GL_FALSE,
			//	layout.GetStride(),
			//	(const void*)(intptr_t)element.Offset);
			glEnableVertexArrayAttrib(m_RendererID, m_VertexBufferIndex);
			glVertexArrayVertexBuffer(m_RendererID, m_VertexBufferIndex, 
				std::dynamic_pointer_cast<OpenGLVertexBuffer>(vertexBuffer)->m_RendererID,
				element.Offset, layout.GetStride());
			glVertexArrayAttribFormat(m_RendererID, m_VertexBufferIndex, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE,
				0);
			glVertexArrayAttribBinding(m_RendererID, m_VertexBufferIndex, m_VertexBufferIndex);

			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glVertexArrayElementBuffer(m_RendererID,
			std::dynamic_pointer_cast<OpenGLIndexBuffer>(indexBuffer)->m_RendererID);

		m_IndexBuffer = indexBuffer;
	}

}
