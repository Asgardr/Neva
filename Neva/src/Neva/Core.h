#pragma once

#ifdef NV_PLATFORM_WINDOWS
#if NV_DYNAMIC_LINK
	#ifdef NV_BUILD_DLL
		#define NEVA_API __declspec(dllexport)
	#else
		#define NEVA_API __declspec(dllimport)
	#endif
#else
	#define NEVA_API
#endif
#else
	#error Neva only supports Windows!
#endif

#ifdef NV_DEBUG
	#define NV_ENABLE_ASSERTS
#endif

#ifdef NV_ENABLE_ASSERTS
	#define NV_ASSERT(x, ...) {if(!(x)) { NV_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NV_CORE_ASSERT(x, ...) {if(!(x)) { NV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NV_ASSERT(x, ...)
	#define NV_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)