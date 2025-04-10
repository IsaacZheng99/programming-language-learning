#pragma once

#include <iostream>
#include "Vertex3D.h"


// 2.6 destructor, pop elements, and clear the vector
template<typename T>
class Vector6
{
public:
	Vector6() { ReAlloc(2); }

	~Vector6()
	{
		delete[] m_Data;  // destructor
	}

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));

		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(T&& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));

		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	template<typename...Args>
	T& EmplaceBack(Args&&...args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));

		m_Data[m_Size] = T(std::forward<Args>(args)...);

		return m_Data[m_Size++];
	}

	void PopBack()  // pop elements
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();  // manually call the destructor of the poped element
		}
	}

	void Clear()  // clear the vector
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		m_Size = 0;
	}

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

		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			newBlcok[i] = std::move(m_Data[i]);

		delete[] m_Data;
		m_Data = newBlcok;
		m_Capacity = newCapacity;
	}

	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};

template<typename T>
void PrintVector6(const Vector6<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;

	std::cout << "----------" << std::endl;
}

void PrintVector6(const Vector6<Vertex3D>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;

	std::cout << "----------" << std::endl;
}
