#include <iostream>

using namespace std;

bool even(int i)
{
    if (i == 0)
        return true;

    return odd (i - 1);
}

bool odd(int i)
{
    if (i == 0)
        return false;

    return even (i - 1);
}

int main()
{
    cout << even(9);
}
