#include <iostream>

class Entity
{
private:
	bool m_Flag;
public:
	float x, y;

	Entity()
	{
		m_Flag = true;
		x = 0.0f;
		y = 0.0f;
	}

	void Move(float xa, float ya)
	{
		x += xa;
		y += ya;
	}
};

class Player : public Entity
{
public:
	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

void Print(const Entity& entity)
{
	std::cout << entity.x << ", " << entity.y << std::endl;
}

int main()
{
	// 2. inheritance
	Player p;
	p.Move(1.0f, 1.0f);
	p.Print();

	Print(p);
}
