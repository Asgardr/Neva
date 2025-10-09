#include "nvpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Neva {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}