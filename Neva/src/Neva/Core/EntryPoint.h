#pragma once

#ifdef NV_PLATFORM_WINDOWS

extern Neva::Application* Neva::CreateApplication();

int main(int argc, char** argv)
{
	Neva::Log::Init();
	NV_CORE_WARN("Initialized Log!");
	int a = 5;
	NV_INFO("Hello! Var={0}", a);

	auto app = Neva::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Neva only supports Windows!
#endif