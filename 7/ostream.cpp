#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    ostream_iterator<string> oi {cout, " " }; // delimiter optional

    *oi = "Hello";
    oi++; // no-op
    oi = "world"; // The * is also a no-op, it just returns a reference to itself
}
