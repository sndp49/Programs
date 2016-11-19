#include <iostream>
#include <vector>
using namespace std;

class Point
{
public:
    int x, y;

    Point(int xcoord, int ycoord) : x(xcoord), y(ycoord) {}
};

double distance(Point& P1, Point& P2)
{   return sqrt(pow(P2.x - P1.x, 2) + pow(P2.y - P1.y, 2)); }

class data
{
public:
    Point P1, P2;

    int d;

    data() : d(numeric_limits<int>::max()) {}

    data(Point i, Point j, int dist) : P1(i), P2(j), d(dist) {}
};

data bruteForce(int l, int r, const vector<Point>& P)
{
    int dist = numeric_limits<int>::max();
    data *ret = NULL;

    for (int i = l; i<r-1; i++)
    {
        for (int j = i+1; j<r; j++)
        {
            int cur_dist = distance(P[i], P[j]);

            if (cur_dist < dist)
            {
                dist = cur_dist;
                ret = new data(P[i], P[j], cur_dist);
            }
        }
    }

    return *ret;
}

data merge(int d, const vector<Point>& R)
{
    sort(R.begin(), R.end(), [](const Point &lhs, const Point &rhs) -> bool { return lhs.y < rhs.y; });

    data *ret = new data();

    for (int i=0; i<R.size()-1; i++)
    {
        for (int j=i+1; j<R.size() && d > (R[j].y - R[i].y); j++)
        {
            double dist = distance(R[i], R[j]);

            if (ret->d > dist)
                ret = new data(R[i], R[j], dist);
        }
    }

    return *ret;
}

data divide(int l, int r, const vector<Point>& P)
{
    if (r-l<=3)
        return bruteForce(l, r, P);

    int m = l + (r-l)/2;

    data ldata = divide(l, m, P);
    data rdata = divide(m, r, P);

    data l_r_min = (ldata.d < rdata.d) ? ldata : rdata;

    vector<Point> remaining;

    for (point p : P)
    {
        if (abs(p.x - P[m].x) < l_r_min.d)
            remaining.push_back(p);
    }

    data merge_min = merge(l_r_min.d, remaining);

    return (l_r_min.d < merge_min.d) ? l_r_min : merge_min;
}

pair<Point, Point> find_closest_pair_points(vector<Point>& P)
{
    sort(P.begin(), P.end(), [](const Point& lhs, const Point& rhs) -> bool{ return lhs.x < rhs.x; });

    data d = divide(0, P.size(), P);
    return make_pair(d.P1, d.P2);
}
