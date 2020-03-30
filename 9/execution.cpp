#include <execution>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v(5e7);
    iota(v.begin(), v.end(), 0);

    auto f = [](auto & i)
             {
                 cerr << i << " ";
             };

    for_each(v.begin(), v.end(), f);

    cerr << "\n";
    for_each(execution::par, v.begin(), v.end(), f);

    cerr << "\n";
    for_each(execution::par_unseq, v.begin(), v.end(), f);

    // parallelization can help a lot for sort (increase the vector size to see)
    // sort(execution::par, v.begin(), v.end());
}
