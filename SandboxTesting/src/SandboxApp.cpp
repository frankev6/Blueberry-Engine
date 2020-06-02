#include	<BlueberryEngine.h>
#include	 "imgui/imgui.h"

class ExampleLayer : public BE::Layer {
public:

	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0,0,0) {
	
		m_VertexArray.reset(BE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(BE::VertexBuffer::Create(vertices, sizeof(vertices)));
		BE::BufferLayout layout = {
			{ BE::ShaderDataType::Float3, "a_Position" },
			{ BE::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(BE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new BE::Shader(vertexSrc, fragmentSrc));


	}

	void OnUpdate(BE::Time t) override {

		BE_TRACE("delta time: {0}",t.GetSeconds());

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

		BE::Renderer::Submit(m_VertexArray, m_Shader);

		BE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}
	
	void OnEvent(BE::Event& event) override {
		//BE::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<BE::KeyPressedEvent>(BE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		
	}


private:

	std::shared_ptr<BE::Shader> m_Shader;
	std::shared_ptr<BE::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<BE::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<BE::VertexArray> m_VertexArray;

	BE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float camSpeed = 2;
	float camRotation = 0.0f;
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