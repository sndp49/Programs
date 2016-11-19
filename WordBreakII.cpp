#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

/*Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

Soln:   Pb: 15.12 Pg.121    */

bool wordBreak(string s, unordered_set<string> &dict)
{
    if(dict.empty()) return false;

    vector<bool> dp(s.size()+1,false);
    dp[0]=true;

    for(int i=1;i<=s.size();i++)
    {
        for(int j=i-1;j>=0;j--)
        {
            if(dp[j])
            {
                string word = s.substr(j,i-j);
                if(dict.find(word)!= dict.end())
                {
                    dp[i] = true;
                    break;          //next i
                }
            }
        }
    }

    return dp[s.size()];
}


vector<string> wordBreak(string s, const unordered_set<string> &dict)
{
    vector<int> dp(s.length(), 0);  // dp[i] stores the length of the last string which is present in dict

    for (int i=0; i<s.length(); i++)
    {
        if (dict.find(s.substr(0, i+1)) != dict.end())
            dp[i] = i+1;

        for (int j=0; j<i && dp[i]==0; j++)
        {
            string rem = s.substr(j+1, i-j);

            if (dp[j] != 0 && dict.find(rem) != dict.end())
                dp[i] = i-j;
        }
    }

    vector<string> res;

    if (dp.back())
    {
        int idx = s.length()-1;

        while (idx >= 0)
        {
            res.emplace_back(s.substr(idx-dp[idx]+1, dp[idx]));
            idx -= dp[idx];
        }

        reverse (res.begin(), res.end());
    }

    return res;
}
