#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	MD_PROFILE_FUNCTION();

	m_CheckerboardTexture = Mandas::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	MD_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Mandas::Timestep ts)
{
	MD_PROFILE_FUNCTION();

	// Update
	{
		MD_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		MD_PROFILE_SCOPE("Renderer Prep");
		Mandas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mandas::RenderCommand::Clear();
	}

	{
		MD_PROFILE_SCOPE("Renderer Draw");
		Mandas::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Mandas::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f,0.2f,0.3f,1.0f });
		Mandas::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(30.0f), { 0.8f,0.2f,0.3f,1.0f });
		Mandas::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f,0.3f,0.8f,1.0f });
		//Mandas::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Mandas::Renderer2D::DrawRotatedQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), m_CheckerboardTexture, 10.0f, { 1.0f,0.9f,0.9f,1.0f });
		Mandas::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color 2D", glm::value_ptr(m_SquareColor));

	for (auto&result : m_ProfileResults)
	{
		char label[50];
		MD_CORE_ASSERT(strlen(result.Name) < 50, "The string's len is over the size of buffer!");
		strcpy(label, "%.3fms  ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Mandas::Event& e)
{
	m_CameraController.OnEvent(e);
}
