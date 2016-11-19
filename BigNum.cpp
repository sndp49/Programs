#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

class BigNum
{
    vector<uint8_t> nums;

public:
    BigNum()    {}

    BigNum(int n)
    {   nums.assign(n, 0);  }

    void append(string s)
    {
        for (int i=0; i<s.length(); i++)
            nums.push_back((s[i]-'0')%256);
    }

    void append(char* str)
    {
        for (int i=0; i<strlen(str); i++)
            nums.push_back((str[i]-'0')%256);
    }

    BigNum operator* (BigNum other)
    {
        int m = nums.size(), n = other.nums.size();

        reverse(nums.begin(), nums.end());
        reverse(other.nums.begin(), other.nums.end());

        BigNum res(m+n);

        int i, j, k;

        for (i=0; i<m; i++)
        {
            for (j=0; j<n; j++)
            {
                uint32_t prod = nums[i] * other.nums[j] + res.nums[i+j];

                res.nums[i+j]    = prod%10;
                res.nums[i+j+1] += prod/10;
            }
        }

        for (k = m+n-1; res.nums[k] == 0; k--)
            res.nums.pop_back();

        reverse(res.nums.begin(), res.nums.end());

        return res;
    }

    void print()
    {
        for (int i=0; i<nums.size(); i++)
            printf("%x", nums[i]);
        cout << endl;
    }
};

int main(int argc, char* argv[])
{
    BigNum A, B;

    if (argc == 3)
    {
        A.append(argv[1]);
        B.append(argv[2]);
    }
    else
    {
        A.append("123");
        B.append("456");
    }

    BigNum C = A*B;
    C.print();

    return 0;
}
