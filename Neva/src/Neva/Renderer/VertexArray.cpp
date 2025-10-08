#include "nvpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Neva {

	Neva::VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			NV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::OpenGl:
			return new OpenGLVertexArray();
		}

		NV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}