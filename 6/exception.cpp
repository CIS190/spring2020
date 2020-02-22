void f()
{
    int * p {new int};

    throw 1;

    delete p; // never called, results in a memory leak. If p was a unique_ptr instead, its destructor would be called when the stack is unwound and the allocated memory would be deleted.
}

void g()
{
    int * q {new int}; // similarly, this results in a memory leak as well

    f();

    delete q;
}

int main()
{
    try
    {
        g();
    }
    catch (...)
    {
        // something went wrong, handle it here.
    }
}
