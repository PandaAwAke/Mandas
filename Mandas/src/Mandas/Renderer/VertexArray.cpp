#include "mdpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Mandas {

	Mandas::VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		MD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}