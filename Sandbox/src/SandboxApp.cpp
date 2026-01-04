#include <Neva.h>
#include <Neva/Events/KeyEvent.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Neva::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(Neva::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Neva::Ref<Neva::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Neva::VertexBuffer::Create(vertices, sizeof(vertices)));

		Neva::BufferLayout layout = {
			{ Neva::ShaderDataType::Float3, "a_Position"},
			{ Neva::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		Neva::Ref<Neva::IndexBuffer> indexBuffer;
		indexBuffer.reset(Neva::IndexBuffer::Create(indices, 3));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Neva::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Neva::Ref<Neva::VertexBuffer> squareVB;
		squareVB.reset(Neva::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Neva::BufferLayout squareVBlayout = {
			{ Neva::ShaderDataType::Float3, "a_Position"},
			{ Neva::ShaderDataType::Float2, "a_TexCoord"},
		};

		squareVB->SetLayout(squareVBlayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Neva::Ref<Neva::IndexBuffer> squareIB;
		squareIB.reset(Neva::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = Neva::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}

		)";
		m_FlatColorShader = Neva::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Neva::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Neva::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Neva::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Neva::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Neva::Timestep ts) override
	{
		//Update
		m_CameraController.OnUpdate(ts);

		//Render
		Neva::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Neva::RenderCommand::Clear();

		Neva::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Neva::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Neva::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x) 
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Neva::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Neva::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Neva::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//Neva::Renderer::Submit(m_Shader, m_VertexArray);

		Neva::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Neva::Event& e) override 
	{
		m_CameraController.OnEvent(e);
	}
private:
	Neva::ShaderLibrary m_ShaderLibrary;
	Neva::Ref<Neva::Shader> m_Shader;
	Neva::Ref<Neva::VertexArray> m_VertexArray;

	Neva::Ref<Neva::Shader> m_FlatColorShader;
	Neva::Ref<Neva::VertexArray> m_SquareVA;

	Neva::Ref<Neva::Texture2D> m_Texture, m_ChernoLogoTexture;

	Neva::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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
