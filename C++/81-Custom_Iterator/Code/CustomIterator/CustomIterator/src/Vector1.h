#pragma once

#include "Iterator1.h"


// 2.2 add iterator basics: template, pointer, begin(), and end()
template<typename T>
class Vector1
{
public:
	// same implementation with "std::vector<>"
	using ValueType = T;
	using Iterator = VectorIterator1<Vector1<T>>;
public:
	Vector1() { ReAlloc(2); }

	~Vector1()
	{
		Clear();
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

	Iterator begin()  // begin() and end() are used for range-based for loop
	{
		return Iterator(m_Data);
	}

	Iterator end()
	{
		return Iterator(m_Data + m_Size);
	}
private:
	void ReAlloc(size_t newCapacity)
	{
		// 1. allocate a new block of memory
		// 2. copy/move old elements into the new block
		// 3. delete the old block

		T* newBlcok = (T*)::operator new(newCapacity * sizeof(T));

		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			newBlcok[i] = std::move(m_Data[i]);

		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		::operator delete(m_Data, m_Capacity * sizeof(T));

		m_Data = newBlcok;
		m_Capacity = newCapacity;
	}
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};
