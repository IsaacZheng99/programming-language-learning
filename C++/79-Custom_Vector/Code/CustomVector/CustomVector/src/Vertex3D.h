#pragma once

#include <iostream>


// 2.2 the copy problem
struct Vertex3D
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vertex3D() {}

	Vertex3D(float scalar)
		: x(scalar), y(scalar), z(scalar) {
	}

	Vertex3D(float x, float y, float z)
		: x(x), y(y), z(z) {
	}

	Vertex3D(const Vertex3D& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copy\n";
	}

	Vertex3D(Vertex3D&& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Move\n";
	}

	Vertex3D& operator=(const Vertex3D& other)
	{
		std::cout << "operator= Copy\n";
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vertex3D& operator=(Vertex3D&& other)
	{
		std::cout << "operator= Move\n";
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	~Vertex3D()
	{
		std::cout << "Destroyed\n";
	}
};

// 2.8 add memory block in Vertex3D class
struct Vertex3DWithAllocation
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_MemoryBlock = nullptr;  // add a memory block

	Vertex3DWithAllocation()
	{
		m_MemoryBlock = new int[5];  // allocate storage for five "int" data and we need to delete it when needed
	}

	Vertex3DWithAllocation(float scalar)
		: x(scalar), y(scalar), z(scalar)
	{
		m_MemoryBlock = new int[5];  // allocate storage for five "int" data and we need to delete it when needed
	}

	Vertex3DWithAllocation(float x, float y, float z)
		: x(x), y(y), z(z)
	{
		m_MemoryBlock = new int[5];  // allocate storage for five "int" data and we need to delete it when needed

	}

	Vertex3DWithAllocation(const Vertex3DWithAllocation& other) = delete;  // we won't copy in our case

	Vertex3DWithAllocation(Vertex3DWithAllocation&& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Move\n";

		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
	}

	Vertex3DWithAllocation& operator=(const Vertex3DWithAllocation& other) = delete;  // we won't copy in our case

	Vertex3DWithAllocation& operator=(Vertex3DWithAllocation&& other)
	{
		std::cout << "operator= Move\n";

		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	~Vertex3DWithAllocation()
	{
		std::cout << "Destroyed\n";
		delete[] m_MemoryBlock; // delete when destructing
	}
};
