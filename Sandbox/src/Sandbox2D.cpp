#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles = "aaaaaaaaaaaaaaaaaaaaaaaa"
								"aaaaaaaaaaaaaaaaaaaaaaaa"
								"aaaaaaaaaaaaaaaaaaaaaaaa"
								"aaaaaaaaaaaaaaaaaaaaaaaa"
								"aaaaaaaaDDDDDaaaaaaaaaaa"
								"aaaaaaaaDaaaDaaaaaaaaaaa"
								"aaaaaaaaDaaaDaaaaaaaaaaa"
								"aaaaaaaaDaaaDaaaaaaaaaaa"
								"aaaaaaaaDDDDDaaaaaaaaaaa"
								"aaaaaaaaaaaaaaaaaaaaaaaa"
								"aaaaaaaaaaaaaaaaaaaaaaaa"
								"aaaaaaaaaaaaaaaaaaaaaaaa"
	;

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	MD_PROFILE_FUNCTION();

	m_CheckerboardTexture = Mandas::Texture2D::Create("assets/textures/Checkerboard.png");
	
#if 0
	m_SpriteSheet = Mandas::Texture2D::Create("assets/game/textures/tilemap_packed.png");

	m_TextureTree1 = Mandas::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 22, 7 }, { 16, 16 });
	m_TextureTree2 = Mandas::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 18, 7 }, { 16, 16 }, {3, 3});
	m_TextureStair = Mandas::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 4 }, { 16, 16 });


	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;
	m_TextureMap['a'] = Mandas::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 4 }, { 16, 16 });
	m_TextureMap['D'] = Mandas::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 13, 0 }, { 16, 16 });

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
#endif
	Mandas::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Mandas::Framebuffer::Create(fbSpec);

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

		m_Framebuffer->Bind();

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
		Mandas::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 10.0f, { 1.0f,0.9f,0.9f,1.0f });
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
		m_Framebuffer->Unbind();
	}


#if 0
	if (Mandas::Input::IsMouseButtonPressed(MD_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Mandas::Input::GetMousePosition();
		auto width = Mandas::Application::Get().GetWindow().GetWidth();
		auto height = Mandas::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());


	Mandas::Renderer2D::BeginScene(m_CameraController.GetCamera());
	// MapTiles
	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Mandas::Ref<Mandas::SubTexture2D> texture;

			if (m_TextureMap.find(tileType) != m_TextureMap.end())
			{
				texture = m_TextureMap[tileType];
			}
			else
			{
				texture = m_TextureStair; // Invalid
			}
			Mandas::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
		}
	}
	//Mandas::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureTree1);
	//Mandas::Renderer2D::DrawQuad({ -2.0f, 0.0f, 0.0f }, { 3.0f, 3.0f }, m_TextureTree2);
	//Mandas::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStair);
	Mandas::Renderer2D::EndScene();
#endif
}

void Sandbox2D::OnImGuiRender()
{
	MD_PROFILE_FUNCTION();

	// Note: Switch this to true to enable dockspace.
	static bool dockspaceOpen = false;
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) Mandas::Application::Get().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");

	auto stats = Mandas::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color 2D", glm::value_ptr(m_SquareColor));

	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f });

	ImGui::End();

	ImGui::End();
}

void Sandbox2D::OnEvent(Mandas::Event& e)
{
	m_CameraController.OnEvent(e);
}
