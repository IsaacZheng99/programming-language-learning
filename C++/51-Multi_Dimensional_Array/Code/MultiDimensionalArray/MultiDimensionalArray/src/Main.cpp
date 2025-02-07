#include <iostream>


int main()
{
	// 1. 2D array
	int* array = new int[50];
	int** array2d = new int* [50];  // note that this is not a complete 2D array

	// 2. create and delete complete multi-dimensional arrays
	// 2.1 create
	int** a2d = new int* [50];
	for (int i = 0; i < 50; i++)
		a2d[i] = new int[50];

	//int*** a3d = new int**[50];
	//for (int i = 0; i < 50; i++)
	//	for (int j = 0; j < 50; j++)
	//		a3d[i][j] = new int[50];  // Wrong! runtime error

	int*** a3d = new int** [50];
	for (int i = 0; i < 50; i++)
	{
		a3d[i] = new int* [50];
		for (int j = 0; j < 50; j++)
		{
			a3d[i][j] = new int[50];
			// we can also write in this way:
			//int** ptr = a3d[i];
			//ptr[j] = new int[50];
		}
	}

	a3d[0][0][0] = 1;

	// 2.2 delete
	// delete[] a2d;  // here we just delete the 50 pointers of the top layer and there are 50 * 50 * 4 bytes memory left
	for (int i = 0; i < 50; i++)
		delete[] a2d[i];
	delete[] a2d;

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
			delete[] a3d[i][j];
		delete[] a3d[i];
	}
	delete[] a3d;

	// 2.3 avoid memory fragments
	int* a1d = new int[50 * 50];
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			a1d[j + i * 50] = 1;
	delete[] a1d;
}
