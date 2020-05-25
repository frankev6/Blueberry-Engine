#pragma once
#include "bepch.cpp"
#include <GLFW\glfw3.h>
#include <BlueberryEngine\Window.h>

namespace BE {

	

	class WindowsWindow : public Window
	{
	public:
		
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallbacks(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};


}