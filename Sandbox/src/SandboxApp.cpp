#include <Neva.h>
#include <Neva/Events/KeyEvent.h>

#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Neva::Event& event) override 
	{
		//NV_TRACE("{0}", event.ToString());
		if (event.GetEventType() == Neva::EventType::KeyPressed) {
			Neva::KeyPressedEvent& e = (Neva::KeyPressedEvent&)event;
			NV_TRACE("{0} key is pressed!", (char)e.GetKeyCode());
		}
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
