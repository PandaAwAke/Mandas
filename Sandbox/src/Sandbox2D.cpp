#include "Sandbox2D.h"

#include "ImGui/imgui.h"


#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Mandas::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(Mandas::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Mandas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Mandas::RenderCommand::Clear();

	Mandas::Renderer2D::BeginScene(m_CameraController.GetCamera());


	Mandas::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f,0.2f,0.3f,1.0f });
	Mandas::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f,0.3f,0.8f,1.0f });
	Mandas::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Mandas::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color 2D", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Mandas::Event& e)
{
	m_CameraController.OnEvent(e);
}