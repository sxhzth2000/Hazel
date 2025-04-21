#pragma once
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