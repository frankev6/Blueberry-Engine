#include	<BlueberryEngine.h>
#include	 "imgui/imgui.h"

class ExampleLayer : public BE::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		BE_INFO("ExampleLayer::Update"); 
		if (BE::Input::IsKeyPressed(BE_KEY_TAB))
			BE_TRACE("Tab key is pressed (poll)!");
	}

	/*virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
	*/
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
	}
	~Sandbox()
	{
			
	}
};

BE::Application* BE::CreateApplication() {
	return new Sandbox();
}