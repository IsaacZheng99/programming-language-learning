#pragma once

#include <iostream>


// 6. improve class Log with enum
class Log
{
public:
	enum LogLevel
	{
		LevelError = 0, LevelWarning, LevelInfo
	};
private:
	LogLevel m_LogLevel = LevelInfo;
public:
	void SetLevel(LogLevel level)
	{
		m_LogLevel = level;
	}

	void Error(const char* message)
	{
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]: " << message << std::endl;
	}

	void Warn(const char* message)
	{
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]: " << message << std::endl;
	}

	void Info(const char* message)
	{
		if (m_LogLevel >= LevelInfo)
			std::cout << "[INFO]: " << message << std::endl;
	}
};
