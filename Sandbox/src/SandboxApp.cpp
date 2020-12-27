#include "mdpch.h"
#include <Mandas.h>

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mandas/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Mandas::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(Mandas::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f,  0.0f,  0.8f,  0.2f,  0.8f,  1.0f,
			 0.5f, -0.5f,  0.0f,  0.2f,  0.3f,  0.8f,  1.0f,
			 0.0f,  0.5f,  0.0f,  0.8f,  0.8f,  0.2f,  1.0f
		};
		Mandas::Ref<Mandas::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mandas::VertexBuffer::Create(vertices, sizeof(vertices)));

		Mandas::BufferLayout layout = {
			{ Mandas::ShaderDataType::Float3, "a_Position" },
			{ Mandas::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		// This should behind "SetLayout."
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		Mandas::Ref<Mandas::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mandas::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		float squareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f,  0.0f, 1.0f
		};

		m_SquareVA.reset(Mandas::VertexArray::Create());
		Mandas::Ref<Mandas::VertexBuffer> squareVB;
		squareVB.reset(Mandas::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Mandas::ShaderDataType::Float3, "a_Position" },
			{ Mandas::ShaderDataType::Float2, "a_TexCoord" }
		});
		// This should behind "SetLayout."
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Mandas::Ref<Mandas::IndexBuffer> squareIB;
		squareIB.reset(Mandas::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
		m_Shader = Mandas::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Mandas::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		//m_TextureShader = Mandas::Shader::Create("assets/shaders/Texture.glsl");

		m_Texture = Mandas::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Mandas::Texture2D::Create("assets/textures/ChernoLogo.png");
	
		std::dynamic_pointer_cast<Mandas::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Mandas::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}
	
	void OnUpdate(Mandas::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Mandas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mandas::RenderCommand::Clear();

		Mandas::Renderer::BeginScene(m_CameraController.GetCamera());
		//Mandas::Renderer::BeginScene(m_Scene);
		//Mandas::Renderer2D::BeginScene(m_Camera);
		//Mandas::Renderer2D::DrawQuad();
		//Mandas::Renderer2D::DrawCircle(); // fill circle
		//Mandas::Renderer2D::Draw();



		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		

		//Mandas::MaterialRef material = new Mandas::Material(m_FlatColorShader);
		//Mandas::MaterialInstanceRef mi = new Mandas::MaterialInstance(material);

		//mi->SetValue("u_Color", redColor);
		//mi->SetTexture("u_AlbedoMap", texture);
		//squareMesh->SetMaterial(mi);

		std::dynamic_pointer_cast<Mandas::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Mandas::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Mandas::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		Mandas::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		Mandas::Renderer::Submit(textureShader, m_SquareVA,
			//glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * 
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
		);

		// Triangle
		//Mandas::Renderer::Submit(m_Shader, m_VertexArray);

		Mandas::Renderer::EndScene();
		
		// Renderer::Flush();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Mandas::Event& e) override
	{
		m_CameraController.OnEvent(e);

	}

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