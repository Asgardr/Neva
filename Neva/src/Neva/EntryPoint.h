#pragma once

#ifdef NV_PLATFORM_WINDOWS

extern Neva::Application* Neva::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Neva::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Neva only supports Windows!
#endif