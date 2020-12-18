#include "mdpch.h"
#include <Mandas.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Mandas::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Mandas::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f,  0.0f,  0.8f,  0.2f,  0.8f,  1.0f,
			 0.5f, -0.5f,  0.0f,  0.2f,  0.3f,  0.8f,  1.0f,
			 0.0f,  0.5f,  0.0f,  0.8f,  0.8f,  0.2f,  1.0f
		};
		std::shared_ptr<Mandas::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mandas::VertexBuffer::Create(vertices, sizeof(vertices)));

		Mandas::BufferLayout layout = {
			{ Mandas::ShaderDataType::Float3, "a_Position" },
			{ Mandas::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		// This should behind "SetLayout."
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Mandas::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mandas::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		float squareVertices[3 * 4] = {
			-0.75f, -0.75f,  0.0f,
			 0.75f, -0.75f,  0.0f,
			 0.75f,  0.75f,  0.0f,
			-0.75f,  0.75f,  0.0f
		};
		m_SquareVA.reset(Mandas::VertexArray::Create());
		std::shared_ptr<Mandas::VertexBuffer> squareVB;
		squareVB.reset(Mandas::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Mandas::ShaderDataType::Float3, "a_Position" }
			});
		// This should behind "SetLayout."
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Mandas::IndexBuffer> squareIB;
		squareIB.reset(Mandas::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		m_Shader.reset(new Mandas::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Mandas::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}
	
	void OnUpdate(Mandas::Timestep ts) override
	{
		if (Mandas::Input::IsKeyPressed(MD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Mandas::Input::IsKeyPressed(MD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Mandas::Input::IsKeyPressed(MD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Mandas::Input::IsKeyPressed(MD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Mandas::Input::IsKeyPressed(MD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Mandas::Input::IsKeyPressed(MD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Mandas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mandas::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Mandas::Renderer::BeginScene(m_Camera);
		
		Mandas::Renderer::Submit(m_BlueShader, m_SquareVA);
		Mandas::Renderer::Submit(m_Shader, m_VertexArray);

		Mandas::Renderer::EndScene();
		
		// Renderer::Flush();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, world!");
		ImGui::End();
	}

	void OnEvent(Mandas::Event& event) override
	{
	}

private:
	std::shared_ptr<Mandas::Shader> m_Shader;
	std::shared_ptr<Mandas::VertexArray> m_VertexArray;

	std::shared_ptr<Mandas::Shader> m_BlueShader;
	std::shared_ptr<Mandas::VertexArray> m_SquareVA;

	Mandas::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;

};

class Sandbox : public Mandas::Application
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

Mandas::Application* Mandas::CreateApplication()
{
	return new Sandbox();
}