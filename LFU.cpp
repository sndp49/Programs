#include "LFU.h"

int main()
{
    LFU ob(5);

    ob.insert(1, 1);
    ob.insert(2, 2);
    ob.insert(3, 3);
    ob.insert(4, 4);
    ob.insert(5, 5);    ob.print();

    ob.getValue(1);
    ob.getValue(1);
    ob.getValue(2);     ob.print();
    ob.getValue(3);
    ob.getValue(4);     ob.print();

    ob.insert(6, 6);    ob.getValue(6);    ob.print();
    ob.insert(7, 7);    ob.print();

    ob.insert(8, 8); ob.getValue(8); ob.getValue(8); ob.getValue(8); ob.print();

    ob.insert(9, 9); ob.getValue(9); ob.getValue(9); ob.print();

    return 0;
}
