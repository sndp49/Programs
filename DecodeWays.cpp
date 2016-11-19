/*  Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.                                                  */

bool isValid(char c)
{   return (c != '0');  }

bool isValid(char a, char b)
{   return (a == '1' || (a == '2' && b <= '6'));    }


int numDecodings(string s)
{
    if (s.empty() || s[0] == '0')   return 0;
    else if (s.size() == 1)         return 1;

    int res = 0, cur = 1, cur_1 = 1;

    for (int i=1; i<s.length(); i++)
    {
        if ( isValid(s[i]) && isValid(s[i-1], s[i]) )
            res = cur + cur_1;
        else if ( !isValid(s[i]) && isValid(s[i-1], s[i]) )
            res = cur_1;
        else if ( isValid(s[i]) && !isValid(s[i-1], s[i]) )
            res = cur;
        else
            res = 0;

        cur_1 = cur;
        cur = res;
    }

    return res;
}


/*  unordered_map<int, int> map;    // index, count

int Helper(int pos, string s)
{
    if (pos >= s.length())
        return 0;

    if (s[pos] == '0' || (s[pos]-'0' > 26))
        return 0;

    if (s.length()-pos == 1) // last element
        return 1;

    if (map.find(pos) != map.end())
        return map[pos];

    int cnt = 0, val = 0;

    for (int i=pos; i<s.length() && i<pos+2; i++)
    {
        val = (val*10) + (s[i]-'0');

        if (val>0 && val<=26)
        {
            if (i+1==s.length())
                cnt++;
            else
                cnt += Helper(i+1, s);
        }
    }

    map[pos] = cnt;
    return cnt;
}

int numDecodings(string s)
{
    if (s.empty() || s[0] == '0' || s[0]-'0' > 26)
        return 0;

    const int len = s.length();

    int cnt = 0, val = 0;

    for (int i=0; i<2; i++)
    {
        val = (val*10) + (s[i]-'0');

        if (val>0 && val<=26)
        {
            if (i+1==len)
                cnt++;
            else
                cnt += Helper(i+1, s);
        }
    }

    return cnt;
}


// Explanation:
        if both isValid(s[i]) && isValid(s[i-1], s[i]) then the result set of words will be formed by appending s[i] to the words formed till s[i-1] and {s[i-1], s[i]} can be appended to the words formed till s[i-2]
        if isValid(s[i])  && !isValid(s[i-1], s[i])    then the result set of words will be formed by appending s[i] to the words formed till s[i-1]
        if !isValid(s[i]) && isValid(s[i-1], s[i])     then the result set of words will be formed by appending {s[i-1], s[i]} to the words formed till s[i-2]
        if !isValid(s[i]) && !isValid(s[i-1], s[i])    then the result set is 0, because no words can be formed by any combination  

                                                                                                                                   */
