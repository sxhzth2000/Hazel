#pragma once

#include <memory>


#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif // HZ_BUILD_DLL
#else
	#error Hazel only support Windows!
#endif

//bitmask  二进制的1 左移x位
#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)


#define HZ_CORE_ASSERT(x, ...)                                             \
{                                                                      \
if (!(x))                                                          \
{                                                                  \
HZ_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__);           \
__debugbreak();                                                \
}                                                                  \
}


namespace Hazel{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}


