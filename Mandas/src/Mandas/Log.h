#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Mandas {

	class MANDAS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define MD_CORE_TRACE(...)   ::Mandas::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MD_CORE_INFO(...)    ::Mandas::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MD_CORE_WARN(...)    ::Mandas::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MD_CORE_ERROR(...)   ::Mandas::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MD_CORE_FATAL(...)   ::Mandas::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MD_TRACE(...)        ::Mandas::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MD_INFO(...)         ::Mandas::Log::GetClientLogger()->info(__VA_ARGS__)
#define MD_WARN(...)         ::Mandas::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MD_ERROR(...)        ::Mandas::Log::GetClientLogger()->error(__VA_ARGS__)
#define MD_FATAL(...)        ::Mandas::Log::GetClientLogger()->fatal(__VA_ARGS__)

