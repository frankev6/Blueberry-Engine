#include	<BlueberryEngine.h>


class ExampleLayer : public BE::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override { BE_INFO("ExampleLayer::Update"); }

	void OnEvent(BE::Event& event) override { BE_TRACE("{0}", event); }
};


class Sandbox : public BE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new BE::ImGuiLayer());
	}
	~Sandbox()
	{
			
	}
};

BE::Application* BE::CreateApplication() {
	return new Sandbox();
}