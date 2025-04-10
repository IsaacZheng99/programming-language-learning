#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include "CityRecord1.h"
#include "CityRecord2.h"
#include "CityRecord3.h"


int main()
{
	// 2. std::map<>
	// 2.2 some examples
	// 2.2.1 iterate std::vector<> to get an specific element
	std::vector<CityRecord1> cities;
	cities.emplace_back("Melbourne", 5000000, 2.4, 9.4);
	cities.emplace_back("Lol-town", 6000000, 2.4, 9.4);
	cities.emplace_back("Berlin", 7000000, 2.4, 9.4);
	cities.emplace_back("Paris", 8000000, 2.4, 9.4);
	cities.emplace_back("London", 9000000, 2.4, 9.4);

	for (const auto& city : cities)
	{
		if (city.Name == "Berlin")
		{
			std::cout << city.Population << std::endl;
			break;
		}
	}

	// 2.2.2 std::map<>
	std::map<std::string, CityRecord1> cityMap1;
	cityMap1["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityMap1["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityMap1["Berlin"] = CityRecord1("Berlin", 7000000, 2.4, 9.4);
	cityMap1["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityMap1["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	CityRecord1& berlinData1 = cityMap1["Berlin"];
	std::cout << berlinData1.Population << std::endl;

	// 2.2.3 operator[] of std::map<>
	std::map<std::string, CityRecord1> cityMap2;
	cityMap2["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityMap2["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityMap2["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityMap2["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	CityRecord1& berlinData2 = cityMap2["Berlin"];
	berlinData2.Name = "Berlin";
	berlinData2.Population = 7000000;
	std::cout << cityMap2["Berlin"].Population << std::endl;

	// in both cases, we can insert a "CityRecord1" but in the second case we need to "copy"
	// so choose the case 1 to avoid copy and create in place
	CityRecord1 berlinData3;
	berlinData3.Name = "Berlin";
	berlinData3.Population = 7000001;
	cityMap2["Berlin"] = berlinData3;
	std::cout << cityMap2["Berlin"].Population << std::endl;

	// there is no "const" version of the "operator[]"
	const auto& referenceCityMap2 = cityMap2;
	//const CityRecord1& berlinData4 = referenceCityMap2["Berlin"];  // Wrong! Compiling error. error C2678: binary '[': no operator found which takes a left-hand operand of type 'const std::map<std::string,CityRecord,std::less<std::string>,std::allocator<std::pair<const std::string,CityRecord>>>' (or there is no acceptable conversion)

	// 2.2.4 at() function
	std::map<std::string, CityRecord1> cityMap3;
	cityMap3["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityMap3["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityMap3["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityMap3["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	// CityRecord1& berlinData5 = cityMap3.at("Berlin");  // Wrong! Runtime error.

	std::map<std::string, CityRecord1> cityMap4;
	cityMap4["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityMap4["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityMap4["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityMap4["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	if (cityMap4.find("Berlin") != cityMap4.end())
	{
		CityRecord1& berlinData5 = cityMap4.at("Berlin");
		std::cout << berlinData5.Population << std::endl;
	}

	// 2.2.5 take CityRecord as the key
	std::map<CityRecord2, uint32_t> foundedMap;  // type of the key is "CityRecord"
	foundedMap[CityRecord2{ "Melbourne", 5000000, 2.4, 9.4 }] = 1850;
	foundedMap[CityRecord2{ "Paris", 8000000, 2.4, 9.4 }] = 1888;
	std::cout << foundedMap[CityRecord2{ "Paris", 8000000, 2.4, 9.4 }] << std::endl;

	for (auto& [city, year] : foundedMap)
	{
		std::cout << city.Name << " " << city.Population << " " << year << std::endl;
	}

	// 3. std::unordered_map<>
	// 3.2 some examples
	// 3.2.1 std::unordered_map<>
	std::unordered_map<std::string, CityRecord1> cityUnorderedMap1;
	cityUnorderedMap1["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityUnorderedMap1["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityUnorderedMap1["Berlin"] = CityRecord1("Berlin", 7000000, 2.4, 9.4);
	cityUnorderedMap1["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityUnorderedMap1["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	CityRecord1& berlinData6 = cityUnorderedMap1["Berlin"];
	std::cout << berlinData6.Population << std::endl;

	// 3.2.3 take CityRecord as the key
	std::unordered_map<CityRecord3, uint32_t> foundedUnorderedMap;  // type of the key is "CityRecord"
	foundedUnorderedMap[CityRecord3{ "Melbourne", 5000000, 2.4, 9.4 }] = 1850;
	uint32_t melbourneFounded = foundedUnorderedMap[CityRecord3{ "Melbourne", 5000000, 2.4, 9.4 }];
	std::cout << melbourneFounded << std::endl;

	// 4. iterate through a map
	std::unordered_map<std::string, CityRecord1> cityUnorderedMap2;
	cityUnorderedMap2["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityUnorderedMap2["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityUnorderedMap2["Berlin"] = CityRecord1("Berlin", 7000000, 2.4, 9.4);
	cityUnorderedMap2["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityUnorderedMap2["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	for (auto& kv : cityUnorderedMap2)
	{
		const std::string& name = kv.first;
		CityRecord1 city = kv.second;
		std::cout << name << " " << city.Population << std::endl;
	}

	for (auto& kv : cityUnorderedMap2)
	{
		auto& name = kv.first;
		auto& city = kv.second;
		std::cout << name << " " << city.Population << std::endl;
	}

	for (auto& [name, city] : cityUnorderedMap2)
	{
		std::cout << name << " " << city.Population << std::endl;
	}

	// 5. remove a specific element: erase()
	std::unordered_map<std::string, CityRecord1> cityUnorderedMap3;
	cityUnorderedMap3["Melbourne"] = CityRecord1("Melbourne", 5000000, 2.4, 9.4);
	cityUnorderedMap3["Lol-town"] = CityRecord1("Lol-town", 6000000, 2.4, 9.4);
	cityUnorderedMap3["Berlin"] = CityRecord1("Berlin", 7000000, 2.4, 9.4);
	cityUnorderedMap3["Paris"] = CityRecord1("Paris", 8000000, 2.4, 9.4);
	cityUnorderedMap3["London"] = CityRecord1("London", 9000000, 2.4, 9.4);

	cityUnorderedMap3.erase("Paris");
	cityUnorderedMap3.erase("Paris123");

	for (auto& [name, city] : cityUnorderedMap3)
	{
		std::cout << name << " " << city.Population << std::endl;
	}
}
