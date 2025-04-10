#pragma once

#include <iostream>


// 2.2.5 take CityRecord as the key
struct CityRecord2
{
	std::string Name;
	uint64_t Population;
	double Latitude, Longitude;

	CityRecord2() = default;

	CityRecord2(std::string name, uint64_t population, double latitude, double longitude)
		: Name(name), Population(population), Latitude(latitude), Longitude(longitude) {
	}

	bool operator<(const CityRecord2& other) const
	{
		return Population < other.Population;
		// in fact, this temporary implementation is wrong 
		// because when "Population >= other.Population" the "operator<" will return "false"
		// and in this case "std::map" will take them as the same keys
		// and the latter "key" won't be inserted but the latter "value" will replace the former "value"
		// moreover, "operator<" will be used for other purposes, so implement it properly
	}
};
