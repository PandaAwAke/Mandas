#include "mdpch.h"
#include "Renderer.h"

namespace Mandas {

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();	// Should be stay here instead of inside DrawIndexed!
		RenderCommand::DrawIndexed(vertexArray);
	}

}