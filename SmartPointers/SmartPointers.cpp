// SmartPointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Shared_ptr.h"
#include "Unique_ptr.h"

void Test_Shared_ptr() 
{
	Shared_ptr<int> ptr1(new int(100));
	cout << " -- Shared pointer ptr1 --\n";
	cout << ptr1;
	{
		Shared_ptr<int> ptr2 = ptr1;
		cout << " --  Shared Pointer ptr1, ptr2 -- \n";
		cout << ptr1;
		cout << ptr2;
		{
			Shared_ptr<int> ptr3(ptr2);
			cout << " --  Shared Pointer ptr1, ptr2,ptr3 -- \n";
			cout << ptr1;
			cout << ptr2;
			cout << ptr3;
		}

		cout << " --  Shared Pointer ptr1, ptr2 -- \n";
		cout << ptr1;
		cout << ptr2;
	}

	cout << " -- Shared pointer ptr1 --\n";
	cout << ptr1;

}

void Test_Unique_ptr()
{
	struct X {};
	struct Y : public X {};
	struct Z {};

	Unique_ptr<X> x(new X);
	cout << " -- Unique pointer x --\n";
	cout << x << endl;

	Unique_ptr<Y> y(new Y);
	cout << " -- Unique pointer x and y --\n";
	cout << x << endl;
	cout << y << endl;

	// Should be able to point to derived class
	x = std::move(y);
	cout << " -- Unique pointer x and y after move --\n";
	cout << x << endl;
	cout << y << endl;

	Unique_ptr<X> z(std::move(y));
	cout << " -- Unique pointer x, y and z --\n";
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
}

int main(int argc, char* argv[])
{
	cout << "Testing Unique Ptr :" << endl;
	Test_Unique_ptr();
	cout << "Testing Shared Pointer : " << endl;
	Test_Shared_ptr();

	return 0;
}

