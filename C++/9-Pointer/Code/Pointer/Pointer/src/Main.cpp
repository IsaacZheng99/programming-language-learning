#include <iostream>


int main()
{
	// 2. null pointer
	void* nptr1 = 0;
	void* nptr2 = NULL;
	void* nptr3 = nullptr;

	int* nptr4 = nullptr;
	std::cout << nptr4 << std::endl;
	double* nptr5 = nullptr;
	std::cout << nptr5 << std::endl;

	// 3. dereference
	int var = 8;
	int* ptr1 = &var;
	std::cout << *ptr1 << std::endl;

	//void* ptr2 = &var;
	//std::cout << *ptr2 << std::endl;  // Wrong!
	//*ptr2 = 9;  // Wrong!

	//std::cout << *nptr1 << std::endl;  // Wrong!

	//std::cout << *nptr4 << std::endl;  // Wrong!
	//*nptr4 = 1;  // Wrong!

	// 4. create data on the stack or the heap
	// on the stack
	int a = 1;

	// on the heap
	char* buffer = new char[8];  // ask for 8-byte heap memory
	memset(buffer, 0, 8);  // set "value = 0" for 8-byte data
	delete[] buffer;
}
