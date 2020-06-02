#include "bepch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "BlueberryEngine/Renderer/Renderer.h"
#include <GLFW\glfw3.h>


namespace BE
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BE_C_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
			   
	}

	Application::~Application() {
	
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch <WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}

	}

	void Application::Run() {
		while (m_Running) {

			float CurrentTime = (float)glfwGetTime();// change later
			Time time = CurrentTime - m_LastFrameTime;
			m_LastFrameTime = CurrentTime;


			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(time);
			}

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
	
		m_Running = false;
		return true;
	}

}