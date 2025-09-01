#include <Neva.h>

class Sandbox : public Neva::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Neva::Application* Neva::CreateApplication()
{
	return new Sandbox();
}
