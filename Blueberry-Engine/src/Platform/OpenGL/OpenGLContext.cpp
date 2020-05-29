#include "bepch.h"
#include "OpenGLContext.h"
#include <GLFW\glfw3.h>
#include <glad/glad.h>

namespace BE
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{

		BE_C_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BE_C_ASSERT(status, "Failed to initialize GLAD")
	}
	void OpenGLContext::SwapBuffers(){
		glfwSwapBuffers(m_WindowHandle);
	
	}

}