#pragma once

#include <iostream>


// 2. std::map<>
// 2.2 some examples
// 2.2.1 iterate std::vector<> to get an specific element
struct CityRecord1
{
	std::string Name;
	uint64_t Population;
	double Latitude, Longitude;

	CityRecord1() = default;

	CityRecord1(std::string name, uint64_t population, double latitude, double longitude)
		: Name(name), Population(population), Latitude(latitude), Longitude(longitude) {
	}
};
