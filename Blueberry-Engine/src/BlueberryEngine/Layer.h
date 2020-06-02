#pragma once
#include "BlueberryEngine/Core/Time.h"
#include "BlueberryEngine/Core.h"
#include "BlueberryEngine/Events/Event.h"


namespace BE
{
	class  Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time t) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};
}