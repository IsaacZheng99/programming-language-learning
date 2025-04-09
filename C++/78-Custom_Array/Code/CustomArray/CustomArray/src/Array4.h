#pragma once


// 3.4 add reference to the return value of operator[]
template<typename T, size_t S>
class Array4
{
public:
	constexpr size_t Size() const { return S; }

	T& operator[](size_t index)
	{
		return m_Data[index];
	}
private:
	T m_Data[S];
};
