https://leetcode.com/problems/longest-valid-parentheses/

Soln: https://leetcode.com/discuss/7609/my-o-n-solution-using-a-stack
        https://discuss.leetcode.com/topic/2426/my-dp-o-n-solution-without-using-stack

int longestValidParentheses(string s) {
    int n = s.length();

    if (s.empty() || n == 1)
        return 0;

    vector<int> dp(n, 0);
    int cur_max = 0;


    for (int i=1; i<n; i++)
    {
        if (s[i] == '(')
            dp[i] = 0;
        else if (s[i] == ')')
        {
            if (s[i-1] == '(')
                dp[i] = (i>1) ? dp[i-2] + 2 : 2;
            else                                            // s[i-1] == ')'
            {
                if (i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(')
                    dp[i] = dp[i-1] + 2 + (i-dp[i-1]-2 >= 0 ? dp[i-dp[i-1]-2] : 0);
            }
        }

        cur_max = max(cur_max, dp[i]);
    }

    return dp.back();
}
