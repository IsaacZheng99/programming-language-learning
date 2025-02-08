#include <iostream>


// 2.2 type punning and union
struct Vector2
{
	float x, y;
};


struct Vector4
{
	float x, y, z, w;

	Vector2& GetFirstVector2()
	{
		return *(Vector2*)&x;  // type punning
	}

	Vector2& GetSecondVector2()
	{
		return *(Vector2*)&z;  // type punning
	}
};


struct Vector4Union
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			Vector2 a, b;
		};
	};
};


void PrintVector2(const Vector2& vector2)
{
	std::cout << vector2.x << ", " << vector2.y << std::endl;
}


int main()
{
	// 2.1 occpy the memory of one variable
	struct Union
	{
		union
		{
			double a;
			int b;
		};
	};

	Union u;
	u.b = 2;
	std::cout << u.a << ", " << u.b << std::endl;
	std::cout << sizeof(Union) << std::endl;

	// 2.2 type punning and union
	Vector4 vector4 = { 1.0f, 2.0f, 3.0f, 4.0f };
	PrintVector2(vector4.GetFirstVector2());
	PrintVector2(vector4.GetSecondVector2());

	Vector4Union vector4Union = { 1.0f, 2.0f, 3.0f, 4.0f };
	PrintVector2(vector4Union.a);
	PrintVector2(vector4Union.b);
	vector4Union.z = 123;
	PrintVector2(vector4Union.b);
}
