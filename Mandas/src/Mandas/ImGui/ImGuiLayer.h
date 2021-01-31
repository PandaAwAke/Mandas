#pragma once

#include "Mandas/Core/Layer.h"

#include "Mandas/Events/ApplicationEvent.h"
#include "Mandas/Events/KeyEvent.h"
#include "Mandas/Events/MouseEvent.h"

namespace Mandas {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		
	private:
		//bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		//bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		//bool OnMouseMovedEvent(MouseMovedEvent& e);
		//bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		//bool OnKeyPressedEvent(KeyPressedEvent& e);
		//bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		//bool OnKeyTypedEvent(KeyTypedEvent& e);
		//bool OnWindowResizeEvent(WindowResizeEvent& e);
		
		
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0;

	};

}