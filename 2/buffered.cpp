#include <iostream>

using namespace std;

int main()
{
	// doesn't print due to buffering
	cout << "asdfasdf";
	abort();

	// the following 3 do work
	// cout << "asdfasdf" << endl;
	// abort();

	// cout << "asdfasdf";
	// cout.flush();
	// abort();

	// cerr << "asdfasdf";
	// abort();
}
