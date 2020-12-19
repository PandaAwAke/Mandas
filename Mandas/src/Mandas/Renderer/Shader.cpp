#include "mdpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Mandas {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		MD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}