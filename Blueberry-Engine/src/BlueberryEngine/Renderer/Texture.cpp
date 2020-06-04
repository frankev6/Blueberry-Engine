#include "bepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace BE
{
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		BE_C_ASSERT(false, "Uknown RendererAPI!");
		return nullptr;
		
	}
}