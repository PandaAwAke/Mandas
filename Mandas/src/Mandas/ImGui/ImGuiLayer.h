#pragma once

#include "Mandas/Layer.h"

#include "Mandas/Events/ApplicationEvent.h"
#include "Mandas/Events/KeyEvent.h"
#include "Mandas/Events/MouseEvent.h"

namespace Mandas {
	class MANDAS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
		//void OnEvent(Event& event) override;
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
		float m_Time = 0.0;

	};

}