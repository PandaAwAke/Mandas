#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	float squareVertices[3 * 4] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f
	};

	m_SquareVA = Mandas::VertexArray::Create();
	Mandas::Ref<Mandas::VertexBuffer> squareVB;
	squareVB.reset(Mandas::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Mandas::ShaderDataType::Float3, "a_Position" }
	});
	// This should behind "SetLayout."
	m_SquareVA->AddVertexBuffer(squareVB);
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Mandas::Ref<Mandas::IndexBuffer> squareIB;
	squareIB.reset(Mandas::IndexBuffer::Create(squareIndices, 6));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Mandas::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Mandas::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<Mandas::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Mandas::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	m_FlatColorShader->Bind();
	Mandas::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Mandas::Renderer::EndScene();

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
