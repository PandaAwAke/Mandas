#pragma once
#include <Mandas.h>

class ExampleLayer : public Mandas::Layer
{
public:
	ExampleLayer();
	void OnUpdate(Mandas::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Mandas::Event& e) override;

private:
	Mandas::ShaderLibrary m_ShaderLibrary;
	Mandas::Ref<Mandas::Shader> m_Shader;
	Mandas::Ref<Mandas::VertexArray> m_VertexArray;

	Mandas::Ref<Mandas::Shader> m_FlatColorShader;
	Mandas::Ref<Mandas::VertexArray> m_SquareVA;

	Mandas::Ref<Mandas::Texture2D> m_Texture, m_LogoTexture;

	Mandas::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};