class list
{
public:
    list(int size) {}
    list(int first, int second) {} // first two elements of the list, or something
};

void printList(list l)
{
    // ...
}

int main()
{
    printList(1); // maybe we expect to print the list with the contents [1]?
    printList({1, 2});
}
