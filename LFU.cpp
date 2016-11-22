#include "LFU.h"

int main()
{
    LFU ob(5);

    ob.insert(1, 1);
    ob.insert(2, 2);
    ob.insert(3, 3);
    ob.insert(4, 4);
    ob.insert(5, 5);    ob.print();

    ob.get(1);
    ob.get(1);
    ob.get(2);          ob.print();
    ob.get(3);
    ob.get(4);          ob.print();

    ob.insert(6, 6);    ob.get(6);  ob.print();
    ob.insert(7, 7);    ob.print();

    ob.insert(8, 8); ob.get(8); ob.get(8); ob.get(8); ob.print();

    ob.insert(9, 9); ob.get(9); ob.get(9); ob.print();

    /*
    LFU ob(2);

    ob.insert(1, 1);
    ob.insert(2, 2);
    cout << ob.get(1) << endl;
    ob.insert(3, 3);
    cout << ob.get(2) << endl;
    cout << ob.get(3) << endl;
    ob.insert(4, 4);
    cout << ob.get(1) << endl;
    cout << ob.get(3) << endl;
    cout << ob.get(4) << endl;              */

    return 0;
}
