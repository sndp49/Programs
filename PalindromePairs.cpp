#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/*  https://leetcode.com/problems/palindrome-pairs/
Given a list of unique words. Find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]                                                                                                                                */

bool isPalindrome(string str)
{
    int s = 0, e = str.length()-1;

    for (;s < e; s++, e--)
    {
        if (str[s] != str[e])
            return false;
    }

    return true;
}

unordered_map<string, int> dict;

vector<vector<int>> palindromePairs(vector<string>& words)
{
    vector<vector<int>> res;

    if (words.empty())
        return res;

    vector<int> empty_strings;

    for (int i=0; i<words.size(); i++)
    {
        if (words[i].empty())
            empty_strings.push_back(i);
        else
        {
            string rev = words[i];  // reverse the string
            reverse(rev.begin(), rev.end());
            dict[rev] = i;
        }
    }

    for (int i=0; i<empty_strings.size(); i++)  // for ex: words = ["a", ""]
    {
        for (int j=0; j<words.size(); j++)
        {
            if (!words[j].empty() && isPalindrome(words[j]))
            {
                res.push_back({j, empty_strings[i]});
                res.push_back({empty_strings[i], j});
            }
        }
    }

    for (int i=0; i<words.size(); i++)
    {
        if (words[i].empty())   continue;

        for (int j=0; j<words[i].length(); j++)
        {
            string l = words[i].substr(0, j+1);
            string r = words[i].substr(j+1);

            if (dict.find(l) != dict.end() && isPalindrome(r) && dict[l] != i)
                res.push_back({i, dict[l]});

            if (dict.find(r) != dict.end() && isPalindrome(l) && dict[r] != i)
                res.push_back({dict[r], i});
        }
    }

    return res;
}
