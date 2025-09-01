#pragma once

#include "Core.h"

namespace Neva {

	class NEVA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();

}
