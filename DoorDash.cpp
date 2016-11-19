/*  Given a set of restaurant timings and Door Dash times. Result set would be times when door dash is open

    R = [(8, 10), (11, 22)]
    DD = [(9, 12), (14, 17), (21, 23)]

    => [(9, 10), (11, 12), (14, 17), (21, 22)]                                                              */

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> mergeIntervals(const vector<vector<int>>& R, const vector<vector<int>>& DD)
{
    vector<vector<int>> res;

    for (int i=0; i<R.size(); i++)
    {
        for (int j=0; j<DD.size(); j++)
        {
            if (R[i][1] < DD[j][0])   // restaurants start time is less than DD's end time
                break;
            else if (DD[j][1] < R[i][0])
                continue;
            else
            {
                if (DD[j][0] <= R[i][0] && R[i][1] <= DD[j][1])   // complete overlap
                {
                    res.push_back({R[i][0], R[i][1]});
                    break;
                }
                else  // partial overlap
                    res.push_back({max(R[i][0], DD[j][0]), min(R[i][1], DD[j][1])});
            }
        }
    }

    return res;
}

int main()
{
    const vector<vector<int>> R = {{8, 10}, {11, 22}};                  // restaurants starting and ending times
    const vector<vector<int>> DD = {{9, 12}, {14, 17}, {21, 23}};       // Door dash starting and ending times

    //const vector<vector<int>> R = {{9, 12}};
    //const vector<vector<int>> DD = {{7, 8}, {13, 22}};

    //const vector<vector<int>> R = {{9, 12}, {14, 17}, {21, 23}};
    //const vector<vector<int>> DD = {{8, 10}, {15, 16}};

    //const vector<vector<int>> R = {{9, 12}, {14, 17}, {21, 23}};
    //const vector<vector<int>> DD = {{8, 10}, {15, 24}};

    vector<vector<int>> res = mergeIntervals(R, DD);

    if (res.empty())
        cout << "No overlap found" << endl;

    for (int i=0; i<res.size(); i++)
        printf("(%d, %d) ", res[i][0], res[i][1]);
    cout << endl;

    return 0;
}
