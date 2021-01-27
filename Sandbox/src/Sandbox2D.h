#pragma once

#include <Mandas.h>

#include "ParticleSystem.h"

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

	Mandas::Ref<Mandas::Texture2D> m_CheckerboardTexture;
	Mandas::Ref<Mandas::Texture2D> m_SpriteSheet;
	Mandas::Ref<Mandas::SubTexture2D> m_TextureTree1, m_TextureTree2, m_TextureStair;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};