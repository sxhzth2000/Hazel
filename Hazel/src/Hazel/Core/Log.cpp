#include "Log.h"



namespace  Hazel {

	 std::shared_ptr<spdlog::logger> Log::s_CoreLogger=nullptr;
	 std::shared_ptr<spdlog::logger> Log::s_ClientLogger=nullptr;

	void Log::Init()
	{

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Hazel");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}

	std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
	{
		if (!s_CoreLogger) Init();
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger>& Log::GetClientLogger()
	{
		if (!s_CoreLogger) Init();
		return s_ClientLogger;
	}


}


