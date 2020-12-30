#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
    DoublyLinkedList<int> list(3);
    list.insert(1, 0);
    list.insert(2, 1);
    list.insert(4, 3);
    cout << list;

    return 0;
}