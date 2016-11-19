#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <priority_queue>
using namespace std;

// https://leetcode.com/problems/rearrange-string-k-distance-apart/

string rearrangeString(string str, int k)
{
  if (k == 0)
      return str;

  int n = str.length();

  string res;

  unordered_map<char, int> cnt;

  for (char ch : str)
      cnt[ch]++;

  priority_queue<pair<int, char>> Q;

  for (auto it = cnt.begin(); it != cnt.end(); it++)
      Q.push(make_pair(it->second, it->first));

  while (!Q.empty())
  {
      vector<pair<int, char>> cache;

      int loops = min(k, n);

      for (int i=0; i<loops; i++)
      {
          if (Q.empty())  return string("");    // do for str = "aaabc", k = 3 

          auto tmp = Q.top();
          Q.pop();

          res += tmp.second;

          if (--tmp.first > 0)
              cache.push_back(tmp);

          n--;
      }

      for (auto pr : cache)    // push elements from the cache back to the Q
          Q.push(pr);
  }

  return res;
}
