#pragma once


// 2.2 add iterator basics: template, pointer, begin(), and end()
template <typename Vector>  // the template "Vector" means the iterator class is used for some kind of "vector"
class VectorIterator1  // iterator class
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator1(PointerType ptr)
		: m_Ptr(ptr) {
	}
private:
	PointerType m_Ptr;
};
