#pragma once

#include "Core.h"

#include "Window.h"
#include "Neva/LayerStack.h"
#include "Events/Event.h"
#include "Neva/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Neva/Renderer/Shader.h"
#include "Renderer/Buffer.h"

namespace Neva {

	class NEVA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();

}
