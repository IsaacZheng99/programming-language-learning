#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include "Profile.h"
#include "Session.h"


// 2. some examples
// 2.1 directly benchmark two functions
// 2.1.1 session
class Instrumentor  // handle session, profile, file writing
{
private:
	InstrumentationSession* m_CurrentSession;
	std::ofstream m_OutputStream;
	int m_ProfileCount;
public:
	Instrumentor()
		: m_CurrentSession(nullptr), m_ProfileCount(0)
	{
	}

	void BeginSession(const std::string& name, const std::string& filePath)
	{
		m_OutputStream.open(filePath);
		WriteHeader();
		m_CurrentSession = new InstrumentationSession({ name });
	}

	void EndSession()
	{
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;
	}

	void WriteProfile(const ProfileResult& result)
	{
		if (m_ProfileCount++ > 0)  // for each function, we have a profile
			m_OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');  // for "json" format

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ",";
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":0,";
		m_OutputStream << "\"ts\":" << result.Start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	// 2.7 multi-thread
	// 2.7.1 session
	void WriteMultiThreadProfile(const MultiThreadProfileResult& result)
	{
		if (m_ProfileCount++ > 0)
			m_OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ",";
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.ThreadID << ",";  // record the thread id
		m_OutputStream << "\"ts\":" << result.Start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	void WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {}, \"traceEvents\":[";

		m_OutputStream.flush();
	}

	void WriteFooter()
	{
		m_OutputStream << "]}";

		m_OutputStream.flush();
	}

	static Instrumentor& Get()
	{
		static Instrumentor* instance = new Instrumentor();
		return *instance;
	}
};
