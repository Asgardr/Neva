#pragma once

#include "Neva.h"

class Sandbox2D : public Neva::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Neva::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Neva::Event& e) override;
private:
	Neva::OrthographicCameraController m_CameraController;

	// Temp
	Neva::Ref<Neva::VertexArray> m_SquareVA;
	Neva::Ref<Neva::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};