#include <iostream>


class Entity
{
private:
	float x, y;
public:
	Entity()
	{
		x = 0.0f;
		y = 0.0f;
		std::cout << "Created Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

void Function()
{
	Entity e;
	e.Print();
}

int main()
{
	Function();
}
