#include <iostream>
#include <fstream>


struct Vector2
{
	float x, y;

	Vector2(float x, float y)
		: x(x), y(y) {
	}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
		// return !operator==(other);
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& vector2)
{
	stream << vector2.x << ", " << vector2.y;
	return stream;
}


int main()
{
	// 2. operator
	Vector2 position(2.0f, 2.0f);
	Vector2 speed(1.0f, 1.0f);
	Vector2 powerup(1.1f, 1.1f);

	Vector2 result1 = position.Add(speed.Multiply(powerup));
	Vector2 result2 = position + (speed * powerup);
	std::cout << result2.x << std::endl;

	std::cout << (result1 == result2) << std::endl;
	std::cout << (result1 != result2) << std::endl;

	std::cout << result1 << std::endl;
}
