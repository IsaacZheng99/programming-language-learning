#pragma once


// 3.2 add constexpr key word
template<typename T, size_t S>
class Array2
{
public:
	constexpr size_t Size() const { return S; }
private:
	T m_Data[S];
};
