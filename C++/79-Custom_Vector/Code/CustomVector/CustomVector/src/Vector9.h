#pragma once

#include <iostream>
#include "Vertex3D.h"


// 2.9 fix the delete bug
template<typename T>
class Vector9
{
public:
	Vector9() { ReAlloc(2); }

	~Vector9()
	{
		Clear();  // not call "delete[]" but manually call the "destructor" of the existing elements
		::operator delete(m_Data, m_Capacity * sizeof(T));
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

		new(&m_Data[m_Size]) T(std::forward<Args>(args)...);

		return m_Data[m_Size++];
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
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

		T* newBlcok = (T*)::operator new(newCapacity * sizeof(T));
		// we don't need to call the "constructor" of the elements here, 
		// we just need to allocate enough memory, 
		// so we don't need to use "T* newBlock = new T[newCapacity]"
		// moreover, note that we have changed the way we "delete" the elements, 
		// we need to change the way we "allocate", 
		// if we still use "T* newBlock = new T[newCapacity]", 
		// there will construct some elemtns that won't be deleted, 
		// leading to memory leak

		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			newBlcok[i] = std::move(m_Data[i]);
		// in fact this is wrong, if we are using "Vector9<std::string>", 
		// this will cause "Exception" because we didn't call 
		// the constructor of the element and 
		// thus the "std::string _Tidy_deallocate()" function will goes wrong 
		// (see more information in "82. Custom Iterator")

	// here is same as "~Vector()"
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		::operator delete(m_Data, m_Capacity * sizeof(T));

		m_Data = newBlcok;
		m_Capacity = newCapacity;
	}

	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};

template<typename T>
void PrintVector9(const Vector9<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;

	std::cout << "----------" << std::endl;
}

void PrintVector9(const Vector9<Vertex3DWithAllocation>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;

	std::cout << "----------" << std::endl;
}
