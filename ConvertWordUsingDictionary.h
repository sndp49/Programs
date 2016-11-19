/*
    Input:  DAMP, LIKE
    Output: DAMP -> LAMP -> LIMP -> LIME -> LIKE            */

// Breadth-First Traversal

start:      the word we’re starting with
stop:       the word we’re ending with
Q:          action queue—words that we must still explore
V:          visited map—maps from word to bool
Parent:     backtrack map (word to word)

Insert start word into Q and V.

While Q is not empty do
    Dequeue word w from Q
    For each possible word v from w with one edit operation
        If v == stop
            Create a linked list called list
            Append v to list

            While w is not the start word
                w = B[w]
                Prepend w to list
                Return list

        If v is a dictionary word
            If not Visited[v]
                Enqueue v in Q
                Visited[v] = true
                B[v] = w

Failure, since we’ve visited everything reachable from the start.

// Soln: Pb. 16.2 Pg. 133


//  https://leetcode.com/problems/word-ladder/

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int Helper(unordered_set<string>& beginSet, unordered_set<string>& endSet, unordered_set<string>& dict, int level)
{
    if (beginSet.empty())   //  if (dict.size() == 0)   dont return 0. check against second ex. in main()
        return 0;

    if (beginSet.size() > endSet.size())
        return Helper(endSet, beginSet, dict, level);

    unordered_set<string> intermediate;    // set containing words which are one edit distance away from words in beginSet

    for (auto bit = beginSet.begin(); bit != beginSet.end(); bit++)
    {
        string word(*bit);

        for (int i=0; i<word.length(); i++)
        {
            char ch = word[i];

            for (int j=0; j<26; j++)
            {
                word[i] = 'a' + j;

                if (word[i] == ch)
                    continue;
                else if (endSet.find(word) != endSet.end())
                    return level+1;
                else if (dict.find(word) != dict.end())
                {
                    dict.erase(word);
                    intermediate.insert(word);
                }
            }

            word[i] = ch;
        }
    }

    return Helper(intermediate, endSet, dict, level+1);
}

int ladderLength(string beginWord, string endWord, unordered_set<string>& dict) {
    if (beginWord == endWord)
        return 1;

    unordered_set<string> beginSet;
    unordered_set<string> endSet;

    beginSet.insert(beginWord);
    dict.erase(beginWord);

    endSet.insert(endWord);
    dict.erase(endWord);

    return Helper(beginSet, endSet, dict, 1);
}

int main()
{
    string beginWord("hit");
    string endWord("cog");
    unordered_set<string> dict = {"hot","dot","dog","lot","log"};

    /*string beginWord("hot");
    string endWord("dog");
    unordered_set<string> dict = {"hot","dot","dog"};*/

    cout << "Length of shortest transformation sequence from beginWord to endWord = " << ladderLength(beginWord, endWord, dict) << endl;
    return 0;
}
