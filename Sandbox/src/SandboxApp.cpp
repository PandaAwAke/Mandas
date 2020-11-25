#include <Mandas.h>



class Sandbox : public Mandas::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Mandas::Application* Mandas::CreateApplication()
{
	return new Sandbox();
}