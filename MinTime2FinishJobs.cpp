#include <iostream>
#include <vector>
using namespace std;

/*http://www.geeksforgeeks.org/find-minimum-time-to-finish-all-jobs-with-given-constraints/         Greedy
Given an array of jobs with different time requirements. There are K identical assignees available and we are also given how much time an assignee takes to do one unit of job. Find the minimum time to finish all jobs with following constraints.

An assignee can be assigned only contiguous jobs. For example, an assignee cannot be assigned jobs 1 and 3, but not 2.
Two assignees cannot share (or co-assigned) a job, i.e., a job cannot be partially assigned to one assignee and partially to other.

Complexity: O(k Log(W) )  where W is the total time taken to finish all jobs                                                                                  */

bool isPossible(const int time, const int k, const vector<int>& jobs)
{
    int emp = 0;            // current employee ID assigned to the job
    int cur_emp_t = 0;      // Time employee used to compete assigned jobs

    int i = 0;

    while (i<jobs.size())
    {
        if (cur_emp_t+jobs[i] > time)
        {
            emp++;
            cur_emp_t = 0;
        }
        else
            cur_emp_t += jobs[i++];
    }

    return (emp < k);
}

int findMinTime(int k, const vector<int> jobs)
{
    int i, start_t = 0, end_t = 0, mid_t, max_job = jobs[0];

    for (i=0; i<jobs.size(); i++)
    {
        end_t += jobs[i];
        max_job = max(max_job, jobs[i]);
    }

    int ans = end_t;

    while (start_t <= end_t)
    {
        mid_t = (start_t+end_t)/2;

        if (mid_t >= max_job && isPossible(mid_t, k, jobs))
        {
            ans = min(ans, mid_t);
            end_t = mid_t-1;
        }
        else
            start_t = mid_t+1;
    }

    return ans;
}

int main()
{
    const vector<int> jobs = {10, 7, 8, 12, 6, 8};
    int k = 4, t = jobs.size();       // K = Number of employees   T = An employee can perform t units of work in unit time

    printf("\nMinimum time to finsh all jobs by %d employee is %d\n", k, findMinTime(k, jobs) * t);

    return 0;
}
