#include <iostream>


// 4. cast Entity* to other pointers
struct Entity
{
	int x, y;

	int* GetPosition()
	{
		return &x;
	}
};


int main()
{
	// 2.1 implicit conversion
	int i1 = 1;
	double d1 = i1;
	std::cout << d1 << std::endl;

	// 2.2 cast int to double
	int i2 = 1;
	double d2 = (double)i2;
	std::cout << d2 << std::endl;

	// 2.3 cast int* to double*
	int i3 = 1;
	double d3 = *(double*)&i3;
	std::cout << d3 << std::endl;

	int i4 = 1;
	double d4 = *(double*)&i4;
	d4 = 0.0;
	std::cout << d4 << std::endl;
	double& d5 = *(double*)&i4;
	//d5 = 0.0;  // Wrong! runtime error

	// 2.4 cast Entity* to other pointers
	Entity e = { 5, 8 };
	int* position = (int*)&e;
	std::cout << position[0] << ", " << position[1] << std::endl;

	int y1 = *(int*)((char*)&e + 4);
	std::cout << y1 << std::endl;
	int y2 = *(int*)((float*)&e + 1);
	std::cout << y2 << std::endl;

	int* pos = e.GetPosition();
	std::cout << pos[0] << ", " << pos[1] << std::endl;
	pos[0] = 123;
	std::cout << pos[0] << ", " << pos[1] << std::endl;
	std::cout << e.x << ", " << e.y << std::endl;
}
