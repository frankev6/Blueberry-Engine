#include "bepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace BE {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
	
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		BE_C_ASSERT(false,"Uknown RendererAPI!" );
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
	
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		BE_C_ASSERT(false, "Uknown RendererAPI!");
		return nullptr;
	}
}