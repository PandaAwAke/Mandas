#include "mdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mandas {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}