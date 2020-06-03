#include "bepch.h"
#include "Shader.h"
#include "Renderer.h"
#include  "Platform/OpenGL/OpenGLShader.h"

namespace BE
{
	Shader* Shader::Create(const std::string& vertextSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertextSrc, fragmentSrc);
		}

		BE_C_ASSERT(false, "Uknown RendererAPI!");
		return nullptr;
	}
}