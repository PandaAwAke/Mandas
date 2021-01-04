#pragma once

#include <Mandas.h>

class Sandbox2D : public Mandas::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Mandas::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Mandas::Event& e) override;

private:
	Mandas::OrthographicCameraController m_CameraController;

	// Temporary
	Mandas::Ref<Mandas::VertexArray> m_SquareVA;
	Mandas::Ref<Mandas::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};