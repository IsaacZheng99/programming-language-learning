#include "Instrumentor.h"
#include "Benchmark1.h"
#include "Benchmark2.h"
#include "Benchmark3.h"
#include "Benchmark4.h"
#include "Benchmark5.h"
#include "Benchmark6.h"
#include "Benchmark7.h"
#include "Benchmark8.h"


int main()
{
	// 2. some examples
	// 2.1 directly benchmark two functions
	// 2.1.3 benchmarking
	Instrumentor::Get().BeginSession("Profile1", "src/json/results1.json");
	Function1();
	Function2();
	Instrumentor::Get().EndSession();

	// 2.2 two functions stack-printing-like run
	Instrumentor::Get().BeginSession("Profile2", "src/json/results2.json");
	RunBenchmarks2();
	Instrumentor::Get().EndSession();

	// 2.3 use marco to open or close the timer
	Instrumentor::Get().BeginSession("Profile3", "src/json/results3.json");
	RunBenchmarks3();
	Instrumentor::Get().EndSession();

	// 2.4 use macro to write the function names automatically
	Instrumentor::Get().BeginSession("Profile4", "src/json/results4.json");
	RunBenchmarks4();
	Instrumentor::Get().EndSession();

	// 2.5 use __FUNCSIG__ to avoid same names of functions
	Instrumentor::Get().BeginSession("Profile5", "src/json/results5.json");
	RunBenchmarks5();
	Instrumentor::Get().EndSession();

	// 2.6 add a namespace to specify the scope
	Instrumentor::Get().BeginSession("Profile6", "src/json/results6.json");
	Benchmark6::RunBenchmarks6();
	Instrumentor::Get().EndSession();

	// 2.7 multi-thread
	Instrumentor::Get().BeginSession("Profile7", "src/json/results7.json");
	Benchmark7::RunBenchmarks7();
	Instrumentor::Get().EndSession();

	// 2.8 multi-thread and call a function
	Instrumentor::Get().BeginSession("Profile8", "src/json/results8.json");
	Benchmark7::RunBenchmarks8();
	Instrumentor::Get().EndSession();
}
