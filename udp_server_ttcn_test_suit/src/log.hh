#ifndef _LOG_HH
#define _LOG_HH

#define LOG_ENABLE 0

#if defined(LOG_ENABLE) && (LOG_ENABLE == 1)
#include <TTCN3.hh>
#define LOG(...) do {\
	TTCN_Logger::log(TTCN_Logger::PARALLEL_UNQUALIFIED, "[%s : %s: %d]: ", __FILE__, __func__, __LINE__);\
	TTCN_Logger::log(TTCN_Logger::PARALLEL_UNQUALIFIED, __VA_ARGS__);\
} while (0)
#else
#define LOG(...)
#endif

#define LOG_ENTER() LOG("Entering")
#define LOG_EXIT() LOG("Leaving")

#endif

