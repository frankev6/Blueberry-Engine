#pragma once

#include "BlueberryEngine/Layer.h"
#include "BlueberryEngine/Events/KeyEvent.h"
#include "BlueberryEngine/Events/MouseEvent.h"
#include "BlueberryEngine/Events/ApplicationEvent.h"

namespace BE
{
	class BE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach();
		void OnDetach();
		 void OnUpdate();
		 void OnEvent(Event& event);

	private:
		float m_Time = 0.0f;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	};
}