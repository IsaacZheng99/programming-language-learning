#pragma once

#include <iostream>
#include <functional>


// 3.2.3 take CityRecord as the key
struct CityRecord3
{
	std::string Name;
	uint64_t Population;
	double Latitude, Longitude;

	CityRecord3() = default;

	CityRecord3(std::string name, uint64_t population, double latitude, double longitude)
		: Name(name), Population(population), Latitude(latitude), Longitude(longitude) {
	}
};


namespace std {

	template<>
	struct hash<CityRecord3>
	{
		size_t operator()(const CityRecord3& key) const
		{
			return hash<std::string>()(key.Name);
		}
	};

	template<>
	struct equal_to<CityRecord3>
	{
		bool operator()(const CityRecord3& lhs, const CityRecord3& rhs) const
		{
			return lhs.Name == rhs.Name;
			//return true;
		}
	};
}
