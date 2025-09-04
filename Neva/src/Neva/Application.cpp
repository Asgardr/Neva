#include "Application.h"

#include "Neva/Events/ApplicationEvent.h"
#include "Neva/Log.h"

namespace Neva {

	Application::Application()
	{
	}



	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication)) 
		{
			NV_TRACE(e.ToString());
		}
		
		if (e.IsInCategory(EventCategoryInput))
		{
			NV_TRACE(e.ToString());
		}

		while (true);
	}
}