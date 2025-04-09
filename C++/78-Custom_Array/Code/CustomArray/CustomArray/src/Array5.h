#pragma once


// 3.5 add const T& operator[]
template<typename T, size_t S>
class Array5
{
public:
	constexpr size_t Size() const { return S; }

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}
private:
	T m_Data[S];
};
