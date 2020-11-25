#pragma once

#ifdef MD_PLATFORM_WINDOWS
	#ifdef MD_BUILD_DLL
		#define MANDAS_API __declspec(dllexport)
	#else
		#define MANDAS_API __declspec(dllimport)
	#endif
#else
	#error Mandas only supports Windows!
#endif

#define BIT(x) (1 << x)