#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


class BigNum
{
public:
    vector<uint8_t> nums;

    BigNum()        {};

    BigNum(int n)   { nums.assign(n, 0); }

    BigNum(unsigned long long int num)  // storing to the base 256
    {
        while (num)
        {
            nums.push_back(num%256);
            num /= 256;
        }

        //reverse(nums.begin(), nums.end());
    }

    BigNum(const BigNum& copy)  // copy constructor
    {
        cout << "Copy constructor called" << endl;
    }

    BigNum operator* (BigNum& other)
    {
        int i, j, k, m = nums.size(), n = other.nums.size();

        BigNum res(m+n);

        for (i=0; i<m; i++)
        {
            for (j=0; j<n; j++)
            {
                uint32_t prod = nums[i] * other.nums[j] + res.nums[i+j];

                res.nums[i+j]    = prod % 256;
                res.nums[i+j+1] += prod / 256;
            }
        }

        return res;
    }

    void printHex()
    {
        for (int i=nums.size()-1; i>=0; i--)
            printf("%02x", nums[i]);                //printf("0x%02x ", nums[i]);
        cout << endl;
    }

    void printDec()
    {
        unsigned long long int num = 0;

        for (int i=0; i<nums.size(); i++)
            num += nums[i] * pow(256, i);

        cout << num << endl;
    }
};

int main()
{
    unsigned long long int num1 = 1234567890;
    unsigned long long int num2 = 255;

    BigNum A(num1), B(num2);
    /*A.printHex();
    A.printDec();

    B.printHex();
    B.printDec();*/

    BigNum C = A*B;

    cout << "A * B = ";
    C.printDec();

    cout << "Base-256 representation of the above Big Integer: ";
    C.printHex();


    return 0;
}
