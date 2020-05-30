#include "bepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include  "Platform/OpenGL/OpenGLVertexArray.h"

namespace BE
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		BE_C_ASSERT(false, "Uknown RendererAPI!");
		return nullptr;
	}
}