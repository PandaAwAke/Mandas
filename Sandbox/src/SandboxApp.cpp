#include "mdpch.h"
#include <Mandas.h>

class ExampleLayer : public Mandas::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}
	
	void OnUpdate() override
	{
		MD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Mandas::Event& event) override
	{
		MD_TRACE("{0}", event);
	}

};

class Sandbox : public Mandas::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Mandas::Application* Mandas::CreateApplication()
{
	return new Sandbox();
}