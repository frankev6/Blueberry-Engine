#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog//fmt/ostr.h"

namespace BE
{

	class BE_API Log
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

//Core log macros
#define BE_C_ERROR(...)	::BE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BE_C_WARN(...)	::BE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BE_C_INFO(...)	::BE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BE_C_TRACE(...)	::BE::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define BE_ERROR(...)	::BE::Log::GetClientLogger()->error(__VA_ARGS__)
#define BE_WARN(...)	::BE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BE_INFO(...)	::BE::Log::GetClientLogger()->info(__VA_ARGS__)
#define BE_TRACE(...)	::BE::Log::GetClientLogger()->trace(__VA_ARGS__)