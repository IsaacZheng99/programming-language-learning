#include <iostream>


//// 2. an example
//void* operator new(size_t size)
//{
//	std::cout << "Allocating " << size << " bytes\n";
//
//	return malloc(size);
//}
//
//void operator delete(void* memory, size_t size)
//{
//	std::cout << "Freeing " << size << " bytes\n";
//
//	free(memory);
//}

struct Object
{
	int x, y, z;
};

// 3. a custom allocation tracker
struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
	s_AllocationMetrics.TotalAllocated += size;

	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;

	free(memory);
}

static void PrintMemoryUsage()
{
	std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}


int main()
{
	//// 2. an example
	//{
	//	std::unique_ptr<Object> obj = std::make_unique<Object>();
	//}

	//std::string name = "xiaoli";

	// 3. a custom allocation tracker
	PrintMemoryUsage();
	std::string string = "xiaoli";
	PrintMemoryUsage();
	{
		std::unique_ptr<Object> object = std::make_unique<Object>();
		PrintMemoryUsage();
	}
	PrintMemoryUsage();
}
