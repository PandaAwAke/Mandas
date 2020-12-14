#include "mdpch.h"
#include "OpenGLContext.h"
#include "Mandas/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Mandas {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MD_CORE_ASSERT(status, "Failed to initialize Glad!");

		MD_CORE_INFO("OpenGL Info:");
		MD_CORE_INFO("   Vendor : {0}", glGetString(GL_VENDOR));
		MD_CORE_INFO("   Renderer : {0}", glGetString(GL_RENDERER));
		MD_CORE_INFO("   Version : {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}