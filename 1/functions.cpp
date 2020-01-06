#include <iostream>

using namespace std;

int triple(int n)
{
	return 3 * n;
}

double triple(double n)
{
	return 3 * n;
}

void printTripleInt(int n)
{
	cout << "3 * " << n << " = " << triple(n) << "\n";
}

int main()
{
	printTripleInt(10);
}
