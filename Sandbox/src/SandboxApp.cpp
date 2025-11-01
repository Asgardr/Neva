#include <Neva.h>
#include <Neva/Events/KeyEvent.h>

#include "imgui/imgui.h"

class ExampleLayer : public Neva::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Neva::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<Neva::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Neva::VertexBuffer::Create(vertices, sizeof(vertices)));

		Neva::BufferLayout layout = {
			{ Neva::ShaderDataType::Float3, "a_Position"},
			{ Neva::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		std::shared_ptr<Neva::IndexBuffer> indexBuffer;
		indexBuffer.reset(Neva::IndexBuffer::Create(indices, 3));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Neva::VertexArray::Create());

		float squareVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Neva::VertexBuffer> squareVB;
		squareVB.reset(Neva::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Neva::BufferLayout squareVBlayout = {
			{ Neva::ShaderDataType::Float3, "a_Position"},
		};

		squareVB->SetLayout(squareVBlayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Neva::IndexBuffer> squareIB;
		squareIB.reset(Neva::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}

		)";

		m_Shader.reset(Neva::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}

		)";

		m_BlueShader.reset(Neva::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Neva::Timestep ts) override
	{
		NV_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliseconds());

		if (Neva::Input::IsKeyPressed(NV_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Neva::Input::IsKeyPressed(NV_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Neva::Input::IsKeyPressed(NV_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Neva::Input::IsKeyPressed(NV_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Neva::Input::IsKeyPressed(NV_KEY_A))
			m_CameraRotation += m_CameraMoveRotation * ts;
		else if (Neva::Input::IsKeyPressed(NV_KEY_D))
			m_CameraRotation -= m_CameraMoveRotation * ts;

		Neva::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Neva::RenderCommand::Clear();

		m_Camera.SetPosition({ m_CameraPosition });
		m_Camera.SetRotation(m_CameraRotation);

		Neva::Renderer::BeginScene(m_Camera);

		Neva::Renderer::Submit(m_BlueShader, m_SquareVA);

		Neva::Renderer::Submit(m_Shader, m_VertexArray);

		Neva::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Neva::Event& event) override 
	{

	}
private:
	std::shared_ptr<Neva::Shader> m_Shader;
	std::shared_ptr<Neva::VertexArray> m_VertexArray;

	std::shared_ptr<Neva::Shader> m_BlueShader;
	std::shared_ptr<Neva::VertexArray> m_SquareVA;

	Neva::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraMoveRotation = 90.0f;	
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
