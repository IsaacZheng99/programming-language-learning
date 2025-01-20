#include <iostream>


static int s_Level = 1;
static int s_Speed = 2;


int main()
{
	// 1. what is ternary operator
	s_Speed = s_Level > 5 ? 10 : 5;
	std::cout << s_Speed << std::endl;

	// return value optimization
	std::string rank = s_Level > 10 ? "Master" : "Beginner";
	std::string otherRank;
	if (s_Level > 10)
		otherRank = "Master";
	else
		otherRank = "Beginner";

	// 3. nest of ternary operator
	s_Speed = s_Level > 5 ? (s_Level > 10 ? 15 : 10) : 5;
	s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;
	std::cout << s_Speed << std::endl;
}
