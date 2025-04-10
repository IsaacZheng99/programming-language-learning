#include <iostream>
#include <bitset>


int main()
{
	// 2. <<
	int i1 = 1;
	int i2 = i1 * 2;  // in fact, the compiler will produce "i2 = i1 << 1;"
	int i3 = i1 << 1;
	std::cout << i1 << ", " << i2 << ", " << i3 << std::endl;

	// 4. | for combining
	// 11111010 & 00001111 = 00001010
	// 1100 << 4 = 11000000
	// 11000000 | 00001010 = 11001010
	int mask = 0b1111;
	int i4 = 0b11101010;
	int i5 = 0b1100;
	// combine i4 and i5
	int i6 = (i4 & mask) | (i5 << 4);
	std::cout << std::bitset<8>(i6) << std::endl;
}
