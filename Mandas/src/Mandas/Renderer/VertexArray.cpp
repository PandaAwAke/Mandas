#include "mdpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Mandas {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}

		MD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}