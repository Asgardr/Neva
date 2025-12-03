#include "nvpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Neva{

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		NV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}