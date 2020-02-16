#include <iostream>
#include <memory>

using namespace std;

class foo
{
public:
	// shared_ptr<foo> other; // never destroyed if there is a cycle
	weak_ptr<foo> other;

	void test()
	{
		if (auto shared = other.lock())
		{
			// do something with the shared_ptr to other
			cerr << "obtained shared_ptr to other\n";
		}
	}

    ~foo()
    {
        cerr << "~foo\n";
    }
};

int main()
{
	{
		auto p {make_shared<foo>()};
		auto q {make_shared<foo>()};

		p->other = q;
		q->other = p;

		p->test();
	}

	cerr << "shared_ptrs both out of scope\n";
}
