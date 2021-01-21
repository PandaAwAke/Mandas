#include "mdpch.h"
#include "OpenGLContext.h"

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
		MD_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MD_CORE_ASSERT(status, "Failed to initialize Glad!");

		MD_CORE_INFO("OpenGL Info:");
		MD_CORE_INFO("   Vendor : {0}", glGetString(GL_VENDOR));
		MD_CORE_INFO("   Renderer : {0}", glGetString(GL_RENDERER));
		MD_CORE_INFO("   Version : {0}", glGetString(GL_VERSION));

		MD_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Mandas requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		MD_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}