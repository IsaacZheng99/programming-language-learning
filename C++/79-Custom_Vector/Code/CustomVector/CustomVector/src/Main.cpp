#include <iostream>
#include <vector>
#include "Vector1.h"
#include "Vertex3D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vector5.h"
#include "Vector6.h"
#include "Vector7.h"
#include "Vector8.h"
#include "Vector9.h"


int main()
{
	// 1. std::vector<>
	std::vector<int> vector;
	vector.reserve(3);
	vector.push_back(1);
	vector.push_back(2);
	vector.emplace_back(3);

	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << std::endl;

	// 2. custom vector
	// 2.1 basics: template, ReAlloc(), PushBack(), operator[], and Size()
	Vector1<std::string> vector1;
	vector1.PushBack("xiaoli");
	vector1.PushBack("C++");
	vector1.PushBack("Vector");

	PrintVector1(vector1);

	// 2.2 the copy problem
	Vector2<Vertex3D> vector2;
	vector2.PushBack(Vertex3D(1.0f));
	vector2.PushBack(Vertex3D(2.0f, 3.0f, 4.0f));
	vector2.PushBack(Vertex3D());

	PrintVector2(vector2);

	// 2.3 add void PushBack(T&& value) to move the temporary value
	Vector3<Vertex3D> vector3;
	vector3.PushBack(Vertex3D(1.0f));
	vector3.PushBack(Vertex3D(2.0f, 3.0f, 4.0f));
	vector3.PushBack(Vertex3D());

	PrintVector3(vector3);

	// 2.4 use std::move() in ReAlloc() function
	Vector4<Vertex3D> vector4;
	vector4.PushBack(Vertex3D(1.0f));
	vector4.PushBack(Vertex3D(2.0f, 3.0f, 4.0f));
	vector4.PushBack(Vertex3D());

	PrintVector4(vector4);

	// 2.5 add EmplaceBack() function
	Vector5<Vertex3D> vector5;
	vector5.EmplaceBack(1.0f);
	vector5.EmplaceBack(2.0f, 3.0f, 4.0f);
	vector5.EmplaceBack();

	PrintVector5(vector5);

	// 2.6 destructor, pop elements, and clear the vector
	Vector6<Vertex3D> vector6;
	vector6.EmplaceBack(1.0f);
	vector6.EmplaceBack(2.0f, 3.0f, 4.0f);
	vector6.EmplaceBack(1.0f, 3.0f, 4.0f);
	vector6.EmplaceBack();
	PrintVector6(vector6);

	vector6.PopBack();
	vector6.PopBack();
	PrintVector6(vector6);

	vector6.EmplaceBack(5.0f, 2.0f, 0.0f);
	vector6.EmplaceBack(1.0f, 7.0f, 9.0f);
	PrintVector6(vector6);

	vector6.Clear();
	PrintVector6(vector6);

	vector6.EmplaceBack(5.0f, 2.0f, 0.0f);
	vector6.EmplaceBack(1.0f, 7.0f, 9.0f);
	PrintVector6(vector6);

	// 2.7 use placement new operator to avoid move and destroy in EmplaceBack()
	Vector7<Vertex3D> vector7;

	vector7.EmplaceBack(1.0f);
	vector7.EmplaceBack(2.0f, 3.0f, 4.0f);
	vector7.EmplaceBack(1.0f, 3.0f, 4.0f);
	vector7.EmplaceBack();
	PrintVector7(vector7);

	vector7.PopBack();
	vector7.PopBack();
	PrintVector7(vector7);

	vector7.EmplaceBack(5.0f, 2.0f, 0.0f);
	vector7.EmplaceBack(1.0f, 7.0f, 9.0f);
	PrintVector7(vector7);

	vector7.Clear();
	PrintVector7(vector7);

	vector7.EmplaceBack(5.0f, 2.0f, 0.0f);
	vector7.EmplaceBack(1.0f, 7.0f, 9.0f);
	PrintVector7(vector7);

	//{
	//	// 2.8 add memory block in Vertex3D class
	//	Vector8<Vertex3DWithAllocation> vector8;

	//	vector8.EmplaceBack(1.0f);
	//	vector8.EmplaceBack(2.0f, 3.0f, 4.0f);
	//	vector8.EmplaceBack(1.0f, 3.0f, 4.0f);
	//	vector8.EmplaceBack();
	//	PrintVector8(vector8);

	//	vector8.PopBack();
	//	vector8.PopBack();
	//	PrintVector8(vector8);

	//	vector8.EmplaceBack(5.0f, 2.0f, 0.0f);
	//	vector8.EmplaceBack(1.0f, 7.0f, 9.0f);
	//	PrintVector8(vector8);

	//	vector8.Clear();
	//	PrintVector8(vector8);

	//	vector8.EmplaceBack(5.0f, 2.0f, 0.0f);
	//	vector8.EmplaceBack(1.0f, 7.0f, 9.0f);
	//	PrintVector8(vector8);
	//}

	{
		// 2.9 fix the delete bug
		Vector9<Vertex3DWithAllocation> vector9;

		vector9.EmplaceBack(1.0f);
		vector9.EmplaceBack(2.0f, 3.0f, 4.0f);
		vector9.EmplaceBack(1.0f, 3.0f, 4.0f);
		vector9.EmplaceBack();
		PrintVector9(vector9);

		vector9.PopBack();
		vector9.PopBack();
		PrintVector9(vector9);

		vector9.EmplaceBack(5.0f, 2.0f, 0.0f);
		vector9.EmplaceBack(1.0f, 7.0f, 9.0f);
		PrintVector9(vector9);

		vector9.Clear();
		PrintVector9(vector9);

		vector9.EmplaceBack(5.0f, 2.0f, 0.0f);
		vector9.EmplaceBack(1.0f, 7.0f, 9.0f);
		PrintVector9(vector9);
	}
}
