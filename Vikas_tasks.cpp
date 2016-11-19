#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

/*
We have a list of various types of tasks to perform. Task types are identified with a character identifier: task A, task B, task C, etc. Each task takes 1 time slot to execute, and once we have executed a task we need N time slots to recover before we can execute another task of the same type. However, we can execute tasks of other types in the meantime. The recovery interval is the same for all task types. We do not reorder the tasks: always execute in order in which we received them on input.

Given a list of input tasks to run, and the cooldown interval, output the minimum number of time slots required to run them in this order.

Example 1
--
Tasks: AABA
Recovery interval: 2
Output: 7 (order is A__AB_A)
                    1234567                                             */

int minTimeSlots (const string& tasks, const int interval, string& res)
{
    unordered_map<char, int> tmap;  // char time_of_visit

    for (int time = 0, i=0; i < tasks.length(); time++)
    {
        if (tmap.find(tasks[i]) == tmap.end())
        {
            tmap[tasks[i]] = time;
            res += tasks[i++];
        }
        else
        {
            if (tmap[tasks[i]]+interval < time)
            {
                tmap[tasks[i]] = time;
                res += tasks[i++];
            }
            else
                res += "-";
        }
    }

    return res.length();
}


int main()
{
    /*string tasks = "AABA";
    int recovery_interval = 2;*/

    string tasks = "ABCDEFBDFABD";
    int recovery_interval = 6;

    string res;

    printf("Minimum number of slots required to execute the following tasks [%s] are %d\n", tasks.data(), minTimeSlots(tasks, recovery_interval, res));

    cout << "Execution: " << res << endl;

    return 0;
}
