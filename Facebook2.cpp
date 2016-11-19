#include "Facebook2.h"
#include <deque>

/*  // Using deque
vector<int> getSorted(BlackBox &B)
{
    deque<int> l, r;

    while (!B.isempty())
    {
        int val = B.peek();

        if (l.empty() && r.empty())
            r.push_back(B.pop());
        else if (!r.empty() && val < r.front())
            r.push_front(B.pop());
        else if (!r.empty() && val > r.front())
        {
            l.push_back(r.front());
            r.pop_front();
            r.push_front(B.pop());
        }
    }

    vector<int> res;

    res.insert(res.end(), l.begin(), l.end());
    res.insert(res.end(), r.begin(), r.end());

    return res;
}
*/


vector<int> getSorted(BlackBox &B)
{
	vector<int> l, r;

	while (!B.isempty())
	{
		if (l.empty() || l.back() <= B.peek())
			l.push_back(B.pop());
		else // l.back() > B.peek()
		{
			while (!l.empty() && l.back() > B.peek())
			{
				r.push_back(l.back());
				l.pop_back();
			}

			l.push_back(B.pop());
		}
	}
	
	while (!r.empty())
	{
		l.push_back(r.back());
		r.pop_back();
	}
	
	return l;
}


int main(int argc, char *argv[])
{
    int n = 10;

    if (argc == 2)
        n = atoi(argv[1]);

    BlackBox b(n);

    vector<int> res = getSorted(b);

    for (int i=0; i<res.size(); i++)
        cout << res[i] << ", ";
    cout << endl;

    return 0;
}
