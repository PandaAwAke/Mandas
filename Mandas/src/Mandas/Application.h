#pragma once

#include "Core.h"

#include "Window.h"
#include "Mandas/LayerStack.h"
#include "Mandas/Events/Event.h"
#include "Mandas/Events/ApplicationEvent.h"

#include "Mandas/ImGui/ImGuiLayer.h"

namespace Mandas {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}