#include <iostream>

using namespace std;

int main()
{
	const int a {0}; // int const is the same
	const int b {1};

	// a++;

	const int * p {&a}; // int const * is the same
	p = &b;

	const int * const q {&a};
	// q = &b;

	cout << *p << " " << *q;
}
