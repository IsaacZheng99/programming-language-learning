#pragma once

#include <chrono>
#include <thread>


// 2.1.2 timer
class InstrumentationTimer
{
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
	bool m_Stopped;
	// 2.7.2 timer
	bool m_MultiThread;
public:
	InstrumentationTimer(const char* name, bool multiThread=false)
		: m_Name(name), m_Stopped(false), m_MultiThread(multiThread)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~InstrumentationTimer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>
			(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>
			(endTimePoint).time_since_epoch().count();

		std::cout << m_Name << ": " << end - start << "us\n";

		// 2.7.2 timer
		if (m_MultiThread)
		{
			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteMultiThreadProfile({ m_Name, start, end, threadID });
		}
		else
			Instrumentor::Get().WriteProfile({ m_Name, start, end });

		m_Stopped = true;
	}
};
