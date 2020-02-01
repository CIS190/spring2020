#include <iostream>
#include <cmath>

using namespace std;

class point
{
private:
	int x;
	int y;

public:
	point(int x, int y) : x {x}, y {y}
	{ }

	void move(int dx, int dy)
	{
		x += dx; // same as this->x += dx;
		y += dy;
	}

	double getDistance() const
	{
		return sqrt(x * x + y * y);
	}
};

int main()
{
	point p {0, 0};
	cout << p.getDistance() << "\n";

	p.move(1, -1);
	cout << p.getDistance() << "\n";
}
