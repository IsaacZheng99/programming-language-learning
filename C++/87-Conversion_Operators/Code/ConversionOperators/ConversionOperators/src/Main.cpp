#include <iostream>
#include <chrono>
#include <variant>


// 2. some examples
// 2.1 simple usage
struct Orange
{
	operator float() { return 5.5f; }
};

// 2.1.3 parameter of function
void PrintFloat(float value)
{
	std::cout << value << std::endl;
}

// 2.2 scoped pointer
// 2.2.1 conditional expression
template <typename T>
class ScopedPtr
{
public:
	ScopedPtr() = default;

	ScopedPtr(T* ptr)
		: m_Ptr(ptr)
	{
	}

	~ScopedPtr()
	{
		delete m_Ptr;
		m_Ptr = nullptr;
	}

	// 2.2.2 direcly add a function to judge
	bool IsValid() const { return m_Ptr != nullptr; }

	// 2.2.3 conversion operator
	operator bool() const { return IsValid(); }

	T* Get()
	{
		return m_Ptr;
	}

	const T* Get() const
	{
		return m_Ptr;
	}
private:
	T* m_Ptr;
};

struct Entity
{
	float X = 0.0f, Y = 0.0f;
};

void ProcessEntity1(const ScopedPtr<Entity>& e)
{
	//if (!e)  // Wrong! Compiling error. error C2088: built-in operator '!' cannot be applied to an operand of type 'const ScopedPtr<Entity>'
	//{
	//	// ...
	//}
}

void ProcessEntity2(const ScopedPtr<Entity>& e)
{
	if (e.IsValid())
	{

	}
}

void ProcessEntity3(const ScopedPtr<Entity>& e)
{
	if (e)
	{

	}
}

// 2.2.4 std::unique_ptr
void ProcessEntity4(const std::unique_ptr<Entity>& e)
{
	if (e)
	{

	}
}

// 2.3 timer
struct Timer
{
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;

	void Start() { m_Start = Clock::now(); }
	void Stop() { m_Stop = Clock::now(); }

	double GetSeconds() const
	{
		using namespace std::chrono;
		return duration_cast<microseconds>(m_Stop - m_Start).count() * 0.001f * 0.001f;
	}

	double GetMilliSeconds() const
	{
		using namespace std::chrono;
		return duration_cast<microseconds>(m_Stop - m_Start).count() * 0.001f;
	}

	// 2.3.2 conversion operator
	operator double() const { return GetSeconds(); }
private:
	TimePoint m_Start, m_Stop;
};

// 2.4 a real world bug
struct PerFrameData
{
	float Time = 0.0f;
	uint32_t Samples = 0;

	PerFrameData() = default;

	PerFrameData(float time)
		: Time(time) {
	}

	operator float() const { return Time; }

	inline PerFrameData& operator+=(float time)
	{
		Time += time;

		return *this;
	}
};

void HandlePerFrameData(std::variant<float, PerFrameData> data)
{
	int index = data.index();
	if (index == 0)
		std::cout << "float: " << std::get<float>(data) << std::endl;
	else if (index == 1)
		std::cout << "PerFrameData: " << std::get<PerFrameData>(data) << std::endl;
}


int main()
{
	// 2. some examples
	// 2.1 simple usage
	// 2.1.1 directly assign
	Orange orange;
	float f = orange;
	std::cout << f << std::endl;

	// 2.1.2 cast
	std::cout << (float)orange << std::endl;

	// 2.1.3 parameter of function
	PrintFloat(orange);

	// 2.2 scoped pointer
	// 2.2.1 conditional expression
	ScopedPtr<Entity> e1 = new Entity();
	Entity* entity = new Entity();
	if (entity)
	{

	}
	if (entity != nullptr)
	{

	}
	if (!entity)
	{

	}

	//if (e1)  // Wrong! Compiling error. error C2451: a conditional expression of type 'const ScopedPtr<Entity>' is not valid
	//{

	//}

	// 2.2.4 std::unique_ptr
	std::unique_ptr<Entity> e2(new Entity());

	// 2.3 timer
	// 2.3.1 directly use timer
	Timer timer1;
	timer1.Start();
	// do something...
	timer1.Stop();
	double time1 = timer1.GetSeconds();

	// 2.3.2 conversion operator
	Timer timer2;
	timer2.Start();
	// do something...
	timer2.Stop();
	double time2 = timer2;

	Timer timer3;
	timer3.Start();
	// do something...
	timer3.Stop();
	double time3 = timer3;

	double totalTime = timer2 + timer3;

	// 2.4 a real world bug
	PerFrameData data(1.0f);
	HandlePerFrameData(data);
	HandlePerFrameData((float)data);

	HandlePerFrameData(data.Time);
}
