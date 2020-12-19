#pragma once

#include <memory>

#ifdef MD_PLATFORM_WINDOWS
#if MD_DYNAMIC_LINK
	#ifdef MD_BUILD_DLL
		#define MANDAS_API __declspec(dllexport)
	#else
		#define MANDAS_API __declspec(dllimport)
	#endif
#else
	#define MANDAS_API
#endif
#else
	#error Mandas only supports Windows!
#endif

#ifdef MD_DEBUG
	#define MD_ENABLE_ASSERTS
#endif

#ifdef MD_ENABLE_ASSERTS
	#define MD_ASSERT(x, ...) { if(!(x)) {MD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }  }
	#define MD_CORE_ASSERT(x, ...) { if(!(x)) {MD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }  }
#else
	#define MD_ASSERT(x, ...)
	#define MD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define MD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Mandas {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}