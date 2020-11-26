#include "mdpch.h"
#include "Application.h"

#include "Mandas/Events/ApplicationEvent.h"
#include "Mandas/Log.h"

namespace Mandas {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// TEST
		WindowResizeEvent e(1280, 720);
		MD_TRACE(e);

		while (true);
	}

}