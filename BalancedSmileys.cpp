#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*  https://www.facebook.com/notes/598486173500621/

Your friend John uses a lot of emoticons when you talk to him on Messenger. In addition to being a person who likes to express himself through emoticons, he hates unbalanced parenthesis so much that it makes him go :(

Sometimes he puts emoticons within parentheses, and you find it hard to tell if a parenthesis really is a parenthesis or part of an emoticon.

A message has balanced parentheses if it consists of one of the following:

- An empty string ""
- One or more of the following characters: 'a' to 'z', ' ' (a space) or ':' (a colon)
- An open parenthesis '(', followed by a message with balanced parentheses, followed by a close parenthesis ')'.
- A message with balanced parentheses followed by another message with balanced parentheses.
- A smiley face ":)" or a frowny face ":("
Write a program that determines if there is a way to interpret his message while leaving the parentheses balanced.

Input
The first line of the input contains a number T (1 ≤ T ≤ 50), the number of test cases.
The following T lines each contain a message of length s that you got from John.

Output
For each of the test cases numbered in order from 1 to T, output "Case #i: " followed by a string stating whether or not it is possible that the message had balanced parentheses. If it is, the string should be "YES", else it should be "NO" (all quotes for clarity only)

Constraints
1 ≤ length of s ≤ 100
                                                                                                                                                                                           */

bool process(string& s)
{
    if (s.empty())
        return false;

    int max_open = 0;
    int min_open = 0;

    for (int i=0; i<s.length(); i++)
    {
        if (s[i] == '(')
        {
            max_open++;

            if (i==0 || s[i-1] != ':')      // if it wasn't part of a smiley, you also increment minOpen.
                min_open++;
        }
        else if (s[i] == ')')
        {
            min_open = max(min_open-1, 0);  // minOpen is negative, reset it to 0.    ex: :))

            if (i==0 || s[i-1] != ':')      // if it wasn't part of a frowny face, decrement maxOpen
                --max_open;

            if (max_open < 0)   break;
        }
    }

    if (max_open >= 0 && min_open == 0)
        return true;
    else
        return false;
}

int main()
{
    int i = 1;

    filebuf fb;

    if (fb.open ("balanced_smileys.txt", ios::in))
    {
        istream is (&fb);

        if (is)
        {
            string s;

            int n = 0;  // no. of lines

            if (getline(is, s))
                n = stoi(s);

            while (getline(is, s))
            {
                if (process(s))
                    cout << i++ << ":\tYES" << endl;
                else
                    cout << i++ << ":\tNO" << endl;
            }
        }
    }

    return 0;
}
