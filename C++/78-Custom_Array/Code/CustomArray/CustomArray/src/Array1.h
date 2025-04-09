#pragma once


// 3.1 two template arguments and Size() function
template<typename T, size_t S>
class Array1
{
public:
	size_t Size() const { return S; }
private:
	T m_Data[S];
};
