#include "mdpch.h"
#include <Mandas.h>
#include <Mandas/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Mandas::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Mandas::Application* Mandas::CreateApplication()
{
	return new Sandbox();
}