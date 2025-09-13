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
		if (Neva::Input::IsKeyPressed(NV_KEY_TAB))
			NV_TRACE("Tab key is pressed!");
	}

	void OnEvent(Neva::Event& event) override 
	{
		//NV_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Neva::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Neva::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Neva::Application* Neva::CreateApplication()
{
	return new Sandbox();
}
