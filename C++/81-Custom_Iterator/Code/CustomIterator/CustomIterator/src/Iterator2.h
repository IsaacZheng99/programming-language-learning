#pragma once


// 2.3 add operators to manipulate custom iterator
template <typename Vector>
class VectorIterator2
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator2(PointerType ptr)
		: m_Ptr(ptr) {
	}

	VectorIterator2& operator++()  // prefix ++
	{
		m_Ptr++;
		return *this;
	}

	VectorIterator2 operator++(int) // postfix ++
	{
		VectorIterator2 iterator = *this;  // this is a cheap "copy" in our case because there is only a pointer "m_Ptr"
		++(*this);  // call "VectorIterator2& operator++()"
		return iterator;
	}

	VectorIterator2& operator--()  // prefix --
	{
		m_Ptr--;
		return *this;
	}

	VectorIterator2 operator--(int)  // postfix --
	{
		VectorIterator2 iterator = *this;
		--(*this);  // call "VectorIterator2& operator--()"
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(m_Ptr + index);
		//return m_Ptr[index];  // this is also fine
	}

	PointerType operator->()
	{
		return m_Ptr;  // return whatever the position we are at has
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const VectorIterator2& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(const VectorIterator2& other) const
	{
		return !(*this == other);  // call "bool operator==(const VectorIterator2& other) const"
		// note that "*this" won't call "operator*()" and it just gets the current object
	}
private:
	PointerType m_Ptr;
};
