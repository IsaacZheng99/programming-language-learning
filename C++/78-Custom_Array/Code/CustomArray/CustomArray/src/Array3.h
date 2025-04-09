#pragma once


// 3.3 add operator[]
template<typename T, size_t S>
class Array3
{
public:
	constexpr size_t Size() const { return S; }

	T operator[](size_t index)
	{
		return m_Data[index];
	}
private:
	T m_Data[S];
};
