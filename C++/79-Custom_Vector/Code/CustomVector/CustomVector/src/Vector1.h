#pragma once
#include <iostream>


// 2. custom vector
// 2.1 basics: template, ReAlloc(), PushBack(), operator[], and Size()
template<typename T>
class Vector1
{
public:
	Vector1() { ReAlloc(2); }  // for simplicity, we allocate storage for 2 elements in advance

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));

		m_Data[m_Size] = value;
		m_Size++;
	}

	// in STL, typically there has an "assert" to check the boundaries in the "Debug" mode, here we ignore it for simplicity
	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	size_t Size() const
	{
		return m_Size;
	}
private:
	void ReAlloc(size_t newCapacity)
	{
		// 1. allocate a new block of memory
		// 2. copy/move old elements into the new block
		// 3. delete the old block

		T* newBlcok = new T[newCapacity];

		// note that this is not we currently need but just a simple check if we are downing the capacity
		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			newBlcok[i] = m_Data[i];  // if we want to use "memcpy()" here, we need to make sure that the "copy constructor" of the element is called correctly because there maybe have something like "deep copy"

		delete[] m_Data;
		m_Data = newBlcok;
		m_Capacity = newCapacity;
	}

	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};

template<typename T>
void PrintVector1(const Vector1<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;

	std::cout << "----------" << std::endl;
}
