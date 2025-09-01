#pragma once

#ifdef NV_PLATFORM_WINDOWS
	#ifdef NV_BUILD_DLL
		#define NEVA_API __declspec(dllexport)
	#else
		#define NEVA_API __declspec(dllimport)
	#endif
#else
	#error Neva only supports Windows!
#endif