#include "nvpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Neva {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGl:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			break;
		}

		NV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}