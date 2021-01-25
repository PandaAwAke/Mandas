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

	//printf("Frame timestep: %f (%f fps)\n", ts.GetSeconds(), 1.0f / ts);

	// Update
	{
		MD_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	Mandas::Renderer2D::ResetStats();
	{
		MD_PROFILE_SCOPE("Renderer Prep");
		Mandas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mandas::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		MD_PROFILE_SCOPE("Renderer Draw");
		Mandas::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Mandas::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(30.0f), { 0.8f,0.2f,0.3f,1.0f });
		Mandas::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f,0.2f,0.3f,1.0f });
		Mandas::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f,0.3f,0.8f,1.0f });
		Mandas::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		//Mandas::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 45.0f, m_CheckerboardTexture, 20.0f);
		Mandas::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 10.0f, { 1.0f,0.9f,0.9f,1.0f });
		Mandas::Renderer2D::EndScene();

		Mandas::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Mandas::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Mandas::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Mandas::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color 2D", glm::value_ptr(m_SquareColor));


	ImGui::End();
}

void Sandbox2D::OnEvent(Mandas::Event& e)
{
	m_CameraController.OnEvent(e);
}
