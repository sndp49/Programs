#include "HeapIndex.h"

int main()
{
    const vector<int> v = {2, 9, 3, 6, 1, 4, 5, 7, 0, 8};

    Heap Q(v);

    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;

    Q.push_back(10);
    cout << Q.top() << endl;

    Q.update(7, 12);
    cout << Q.top() << endl;

    Q.pop(); Q.pop();
    cout << Q.top() << endl;

    Q.update(2, 0);
    cout << Q.top() << endl;

    Q.update(1, 2); Q.pop();
    cout << Q.top() << endl;

    return 0;
}
