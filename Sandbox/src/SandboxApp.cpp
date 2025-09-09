#include <Neva.h>

class ExampleLayer : public Neva::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		NV_INFO("ExampleLayer::Update");
	}

	void OnEvent(Neva::Event& event) override 
	{
		NV_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Neva::Application
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

Neva::Application* Neva::CreateApplication()
{
	return new Sandbox();
}
