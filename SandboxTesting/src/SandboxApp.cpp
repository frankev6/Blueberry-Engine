#include	<BlueberryEngine.h>


class ExampleLayer : public BE::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		BE_INFO("ExampleLayer::Update"); 
		if (BE::Input::IsKeyPressed(BE_KEY_TAB))
			BE_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(BE::Event& event) override {
		
		BE_TRACE("{0}", event); 
	
		if (event.GetEventType() == BE::EventType::KeyPressed)
		{
			BE::KeyPressedEvent& e = (BE::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BE_KEY_TAB)
				BE_TRACE("Tab key is pressed (event)!");
			BE_TRACE("{0}", (char)e.GetKeyCode());
		}
	
	}
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