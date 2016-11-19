#include <iostream>
#include <vector>
#include <priority_queue>
using namespace std;

/*  https://leetcode.com/problems/the-skyline-problem/

Soln: https://discuss.leetcode.com/topic/14939/my-c-code-using-one-priority-queue-812-ms
The idea is to do line sweep and just process the building only at the start and end points.
Use a priority_queue. The Q is sorted by height and then by end position.

For each iteration we find the current building to process, which is either a new building or the one at the top of the priority_queue.

                                                                                                                                                                        */

vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings)
{
    vector<pair<int, int>> res;

    priority_queue<pair<int, int>, vector<pair<int, int>>> Q;   // height, end position

    int i = 0, n = buildings.size(), curX, curH = -1;

    while (i<n || !Q.empty())
    {
        if (Q.empty() || (i<n && Q.top().second >= buildings[i][0]))
        {
            curX = buildings[i][0];

            while (i<n && curX == buildings[i][0])                      // Push all buildings who's starting position comes before the Q.top()'s ending position
            {
                Q.push(make_pair(buildings[i][2], buildings[i][1]));
                i++;
            }
        }
        else    // !Q.empty() && (i>=n || i<n && Q.top().second < buildings[i][0])
        {
            curX = Q.top().second;
            while (!Q.empty() && Q.top().second <= curX)            // Pop all building who's ending position comes before curX's ending position
                Q.pop();
        }

        curH = (Q.empty()) ? 0 : Q.top().first;

        if (res.empty() || res.back().second != curH)
            res.push_back(make_pair(curX, curH));
    }

    return res;
}


/* Working more readable
class data
{
public:
    int h, e;

    data(int end_point, int height) : e(end_point), h(height) {}
};

vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings)
{
    vector<pair<int, int>> res;

    if (buildings.empty())
        return res;

    auto cmp = [](const data &lhs, const data &rhs) { return (lhs.h < rhs.h); };  // the larger height first and if equal height, the one with a bigger end time first    
    priority_queue<data, vector<data>, decltype(cmp)> Q(cmp);

    int i = 0, n = buildings.size(), curX, curH = -1;

    while (i<n || !Q.empty())
    {
        if (Q.empty() || (i<n && Q.top().e >= buildings[i][0]))
        {
            curX = buildings[i][0];

            while (i<n && curX == buildings[i][0])
            {
                Q.emplace(buildings[i][1], buildings[i][2]);
                i++;
            }
        }
        else // !Q.empty() && (i>=n || Q.top().e < buildings[i][0])
        {
            curX = Q.top().e;

            while (!Q.empty() && curX >= Q.top().e)
                Q.pop();
        }

        curH = Q.empty() ? 0 : Q.top().h;

        if (res.empty() || res.back().second != curH)
            res.push_back(make_pair(curX, curH));
    }

    return res;
}                                                                                                                                                                                                                                   */
