#include "bepch.h"
#include "Shader.h"
#include "Renderer.h"
#include  "Platform/OpenGL/OpenGLShader.h"

namespace BE
{

	Ref<Shader> Shader::Create(const std::string& filepath) 
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
			}

			BE_C_ASSERT(false, "Uknown RendererAPI!");
			return nullptr;
		}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertextSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BE_C_ASSERT(false, "RendererAPI: None is currently supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertextSrc, fragmentSrc);
		}

		BE_C_ASSERT(false, "Uknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		BE_C_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader> & shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	BE::Ref<BE::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	BE::Ref<BE::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	BE::Ref<BE::Shader> ShaderLibrary::Get(const std::string& name)
	{
		BE_C_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}