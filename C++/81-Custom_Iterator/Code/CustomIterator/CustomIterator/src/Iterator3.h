#pragma once


// 2.4 fix the ReAlloc() bug
template <typename Vector>
class VectorIterator3
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator3(PointerType ptr)
		: m_Ptr(ptr) {
	}

	VectorIterator3& operator++()
	{
		m_Ptr++;
		return *this;
	}

	VectorIterator3 operator++(int)
	{
		VectorIterator3 iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator3& operator--()
	{
		m_Ptr--;
		return *this;
	}

	VectorIterator3 operator--(int)
	{
		VectorIterator3 iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(m_Ptr + index);
		// return m_Ptr[index]  // this is also fine
	}

	PointerType operator->()
	{
		return m_Ptr;
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const VectorIterator3& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(const VectorIterator3& other) const
	{
		return !(*this == other);
	}
private:
	PointerType m_Ptr;
};
