#include <iostream>
#include <vector>
#include <unordered_map>


// 2.2 bad use of auto
//std::string GetName()
const char* GetName()  // only change the returning type
{
	return "xiaoli";
}

// 2.3 good use of auto
class Device {};

class DeviceManager
{
private:
	std::unordered_map<std::string, std::vector<Device*>> m_Devices;
public:
	const std::unordered_map<std::string, std::vector<Device*>>& GetDevices() const
	{
		return m_Devices;
	}

	const std::unordered_map<std::string, std::vector<Device*>>& GetDevices()
	{
		return m_Devices;
	}
};


int main()
{
	// 1. what can auto do
	auto a = 1;
	std::cout << a << std::endl;
	std::cout << typeid(a).name() << std::endl;

	int b = 1;
	auto c = b;
	std::cout << c << std::endl;
	std::cout << typeid(c).name() << std::endl;

	auto d = 1;
	auto e = d;
	std::cout << d << std::endl;
	std::cout << typeid(d).name() << std::endl;
	std::cout << e << std::endl;
	std::cout << typeid(e).name() << std::endl;

	auto f = 5.5f;
	std::cout << f << std::endl;
	std::cout << typeid(f).name() << std::endl;

	auto l = 1L;
	std::cout << l << std::endl;
	std::cout << typeid(l).name() << std::endl;

	// 2. if we have auto, do we still need to write types?
	// 2.1 in some cases, we only need to change the value on the right hand side of the equal sign
	auto value = 1;
	//auto value = nullptr;
	//auto value = "xiaoli";
	//auto value = 'a';

	// 2.2 bad use of auto
	auto name = GetName();
	std::cout << typeid(name).name() << std::endl;
	//std::cout << name.size() << std::endl;  // Wrong! error C2228: left of '.size' must have class/struct/union

	// 2.3 good use of auto
	std::vector<std::string> strings;
	strings.push_back("Apple");
	strings.push_back("Orange");
	//for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); it++)
	for (auto it = strings.begin(); it != strings.end(); it++)
		std::cout << *it << std::endl;

	DeviceManager dm;
	std::unordered_map<std::string, std::vector<Device*>> devices1 = dm.GetDevices();

	// use using
	using DeviceMap1 = std::unordered_map<std::string, std::vector<Device*>>;
	const DeviceMap1& devices2 = dm.GetDevices();

	// use typedef
	typedef std::unordered_map<std::string, std::vector<Device*>> DeviceMap2;
	const DeviceMap2& devices3 = dm.GetDevices();

	// use auto
	const auto& devices4 = dm.GetDevices();
	const auto devices5 = dm.GetDevices();
	auto devices6 = dm.GetDevices();
}
