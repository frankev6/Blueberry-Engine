#include	<BlueberryEngine.h>
#include	 "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include <glm\glm\gtc\type_ptr.hpp>

class ExampleLayer : public BE::Layer {
public:

	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0), m_trianglePosition(0) {
	
		m_VertexArray.reset(BE::VertexArray::Create());

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,	 1.0f, 1.0f,
			 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		m_VertexBuffer.reset(BE::VertexBuffer::Create(vertices, sizeof(vertices)));
		BE::BufferLayout layout = {
			{ BE::ShaderDataType::Float3, "a_Position" },
			{ BE::ShaderDataType::Float2, "a_TexCoord" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[6] = { 0,1,2,2,3,0 };
		m_IndexBuffer.reset(BE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 v_Color;
			void main()
			{
				color = vec4(v_Color,1.0f);
			}
		)";

		m_FlatColorShader = BE::Shader::Create("VertexPosColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		

		m_FlatColorShader = BE::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		m_Texture = BE::Texture2D::Create("Assets/Textures/BlueStripes.png");

		std::dynamic_pointer_cast<BE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<BE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(BE::Time t) override {
		
		if (BE::Input::IsKeyPressed(BE_KEY_LEFT)) {
			m_CameraPosition.x -= camSpeed * t.GetSeconds();
		}
		if (BE::Input::IsKeyPressed(BE_KEY_RIGHT)) {
			m_CameraPosition.x += camSpeed * t.GetSeconds();
		}
		if (BE::Input::IsKeyPressed(BE_KEY_UP)) {
			m_CameraPosition.y += camSpeed * t.GetSeconds();
		}
		if (BE::Input::IsKeyPressed(BE_KEY_DOWN)) {
			m_CameraPosition.y -= camSpeed * t.GetSeconds();
		}
		if (BE::Input::IsKeyPressed(BE_KEY_R)) {
			camRotation += camSpeed*10 * t.GetSeconds();
		}


		BE::RenderCommand::SetClearColor({ 0.06f, 0.06f, 0.06f, 1 });
		BE::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(camRotation);
		BE::Renderer::BeginScene(m_Camera);


		std::dynamic_pointer_cast<BE::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<BE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("v_Color", m_ShaderColor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_trianglePosition);

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		BE::Renderer::Submit(m_VertexArray, m_FlatColorShader, transform);

		BE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_ShaderColor));
		ImGui::End();
	}
	
	void OnEvent(BE::Event& event) override {
		//BE::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<BE::KeyPressedEvent>(BE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		
	}


private:
	BE::ShaderLibrary m_ShaderLibrary;
	BE::Ref<BE::Shader> m_FlatColorShader;
	BE::Ref<BE::VertexBuffer> m_VertexBuffer;
	BE::Ref<BE::IndexBuffer> m_IndexBuffer;
	BE::Ref<BE::VertexArray> m_VertexArray;

	BE::Ref<BE::Texture2D> m_Texture;

	BE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float camSpeed = 2;
	float camRotation = 0.0f;

	glm::vec3 m_trianglePosition;
	glm::vec3 m_ShaderColor = {255,255,255};
};


class Sandbox : public BE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
			
	}
};

BE::Application* BE::CreateApplication() {
	return new Sandbox();
}