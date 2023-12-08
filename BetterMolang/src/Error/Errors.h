#pragma once
#include <string>
#include <iostream>
#include <stdarg.h>
#include "ColorUtils.h"
#include <mutex>

class Errors
{
public:
	static inline void Error(const char* format, ...)
	{

		va_list args;
		va_start(args, format);
		m_mutex.lock();
		ColorUtils::OutputColoredMessage("31", format, args);
		m_mutex.unlock();
		va_end(args);

		exit(1);
	}

	static inline void Warning(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		m_mutex.lock();
		ColorUtils::OutputColoredMessage("33", format, args);
		m_mutex.unlock();
		va_end(args);
	}

	static inline void Info(const char* format, ...)
	{

		va_list args;
		va_start(args, format);
		m_mutex.lock();
		ColorUtils::OutputColoredMessage("34", format, args);
		m_mutex.unlock();
		va_end(args);
	}
private:
	static std::mutex m_mutex;
};

