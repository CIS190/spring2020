#include <iostream>
#include <memory>

using namespace std;

class foo
{
public:
    void test()
    {
        cerr << "still alive\n";
    }

    ~foo()
    {
        cerr << "~foo\n";
    }
};

int main()
{
    auto p {make_shared<foo>()};
	auto q {p};

	p.reset();

    q->test();
	q.reset();

	cerr << "both shared_ptrs released\n";
}
