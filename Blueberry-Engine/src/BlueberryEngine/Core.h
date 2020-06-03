#pragma once
#include <memory>
/*#ifdef BE_PLATFORM_WINDOWS	
	#ifdef BE_BUILD_DLL

	#endif 
#else
#error	Blueberry only supports Windows
#endif*/

#ifdef BE_DEBUG
	#define BE_ENABLE_ASSERTS	
#endif

#ifdef BE_ENABLE_ASSERTS
#define	BE_ASSERT(x, ...)	{ if (!(x)){BE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#define BE_C_ASSERT(x, ...)	{ if (!(x)){BE_C_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
#define	BE_ASSERT(x, ...)
#define BE_C_ASSERT(x, ...)
#endif 

#define BIT(x) (1 << x)

#define BE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace BE
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}