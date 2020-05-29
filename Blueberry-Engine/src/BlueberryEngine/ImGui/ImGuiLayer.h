#pragma once

#include "BlueberryEngine/Layer.h"
#include "BlueberryEngine/Events/KeyEvent.h"
#include "BlueberryEngine/Events/MouseEvent.h"
#include "BlueberryEngine/Events/ApplicationEvent.h"

namespace BE
{
	class  ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}