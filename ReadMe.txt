Rabin-Karp algorithm => https://www.youtube.com/watch?v=d3TZpfnpJZ0&list=PLc4iJqjcI-1gKfybFRxdD3eqW3-FnX-9V
Knuth–Morris–Pratt   => https://www.youtube.com/watch?v=GTJr8OvyEVQ

http://www.geeksforgeeks.org/the-ubiquitous-binary-search-set-1/

Read OS book (deadlocks, memory management chapters. Read about memcopy and memmove)

enums

2's compliment => https://www.youtube.com/watch?v=n6taPbsRqV4

Matrix multiplication =>  AB(i,j) = Σ(k=0,n) A(i,k)*B(k,j)   Complexity: Ø(n^3)    Given: A(m*n) B(n*p)

Multiply using strings => int tmp = sum[i+j+1] + num1[i] * num2[j] + carry;   carry = tmp/10;   sum[i+j+1] = tmp%10;

Bit addition: A + B => sum[i] = A[i]^B[i]^c                       c (carry bit)
                            c = (A[i]&B[i])|(A[i]&c)|(c&B[i])

Master Theorem => T(n) = aT(n/b)+f(n)   where f(n) is time taken for divide and combine

Bloom Filter

Indirect Sort  =>       bool compare(const int *a, const int *b) { return *a<*b; }

http://www.geeksforgeeks.org/lambda-expression-in-c/
sort(a.begin(), a.end(), [](const int &a, const int &b) -> bool {return a<b;} )   // data type the vector is holding will be the compare fn. parameters

class mycomparision
{
    bool operator() (const int &lhs, const int &rhs)
          return lhs<rhs;         // max heap deafault case
};

typedef priority_queue<int, vector<int>, mycomparision> p_que;
p_que dq;


http://en.cppreference.com/w/cpp/container/unordered_map/unordered_map


//SHA1
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
    unsigned char ibuf[] = "compute sha1";
    unsigned char obuf[20];

    SHA1(ibuf, strlen(ibuf), obuf);

    int i;
    for (i = 0; i < 20; i++) {
        printf("%02x ", obuf[i]);
    }
    printf("\n");

    return 0;
}

#include <openssl/sha.h>

bool simpleSHA256(void* input, unsigned long length, unsigned char* out)
{
    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    if(!SHA256_Final(out, &context))
        return false;

    return true;
}
Usage:

unsigned char out[SHA256_DIGEST_LENGTH]; // 32 bytes
if(!simpleSHA256(<data buffer>, <data length>, out))
{
    // handle error
}


How do you send a const array as reference ?
fn(const int (&arr) [9][9])

const int arr[][9];



int *p = myvector.data();   => return the raw address of the first element in the vector


http://www.cplusplus.com/reference/string/to_string/

https://en.wikipedia.org/wiki/Maximum_subarray_problem  Kadane's algo

http://www.geeksforgeeks.org/merge-two-sorted-linked-lists/

http://www.geeksforgeeks.org/find-the-k-most-frequent-words-from-a-file/

Dijkstra => https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/

http://www.geeksforgeeks.org/boggle-find-possible-words-board-characters/

https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm

http://www.geeksforgeeks.org/stock-buy-sell/

http://www.geeksforgeeks.org/number-of-paths-with-exactly-k-coins/

Levenshtein distance => https://www.youtube.com/watch?v=We3YDTzNXEk

Strtok equivalent =>    stringstream s(string str);
                        while (getline(s, s2, char DELIMETER))

                  (or)  s.find_first_of("aeiou", size_t pos=0);     Replace vowels in a sentence with '*'
                  (or)  strtok_r (re-entrant)

Pg. 271-272 (14.5) 113 (14.17) Pg 332(Interval Tree) Elements of programming Interviews

http://en.cppreference.com/w/cpp/algorithm/partial_sum
for (i=0; i<m; i++)
{
    partial_sum(mat[i].cbegin(), mat[i].cend(), mat[i].begin());

    for (j=0; i>0 && j<n; j++)
        mat[i][j] += mat[i-1][j];
}

Pg.126 : Fit n items into minimum number of 4*12*8 inch priority mail boxes  [Tournament Tree] (Elements of programming Interviews)
class TournamentTreeNode
{
    CapacityType cap;         // leaf: remaining capacity in the box.   non-leaf: max remaining capacity in the subtree
    vector<ItemType> items;   // Store items in the leaf node
};
vector<TournamentTreeNode> TournamentTree;    // left subtree (2i+1)  right subtree (2i+2)

Pg.111 View from above (end point)


Copy => copy (src.begin(), src.end(), back_inserter(dest));

http://geeksquiz.com/insertion-sort-for-singly-linked-list/

subset sum problem DP => https://www.youtube.com/watch?v=s6FhG--P7z0

http://www.geeksforgeeks.org/connect-nodes-at-same-level/

Longest increasing subsequence (monotonically) => http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

Levenstein distance: Problem 15.11 Pg.120

opt(i, j) = min { α(x,y) + opt(i-1, j-1)
                  δ + opt(i, j-1)
                  δ + opt(i-1, j)  }
OR

opt(i,j)  =>  a[i-1] = b[j-1]   opt(i-1, j-1)
              a[i-1] ≠ b[j-1]   1+ min { opt(i-1, j-1),       // replace
                                         opt(i, j-1),         // add
                                         opt(i-1, j)   }      // del

http://articles.leetcode.com/finding-minimum-window-in-s-which/

Node Reweighting: Problem 15.27 Pg. 130
    μ(u)  = w(u) + max (μ(l), μ(r))
    w'(u) = w(u) + μ(r) - (s + μ(u))

Graph:
BFS is used to find the fastest distance from origin to any other vertex. BFS tree has the property that the computed path will be the shortest path from the entrance. (compared to DFS)
DFS is used to detect cycles.
A graph is 2v connected, if by removing any edge, the graph remains connected.  (All edges are part of a cycle)
A graph is 2e connected, if there exists an edge, on removing, the graph remains connected. (A cycle should exist within the graph)
Dijkstra algorithm        Finding the shortest paths between nodes in a graph
Floyd–Warshall algorithm  Finding shortest paths in a weighted graph with positive or negative edge weights (but with no negative cycles)   Pb. 16.11 Pg. 136
Bellman-Ford algorithm    Detects negative weight cycles in O(|V||E|) time    Pb. 16.12 Pg. 137


Median of two sorted arrays => https://www.youtube.com/watch?v=_H50Ir-Tves

Code Segment  - Stores only code.
BSS (Block Started by Symbols) segment - Stores un-initialized global and static variables. It's usually adjacent to the data segment.
Stack segment - stores all the local variables and other informations regarding function return address etc. Parameters, local variables, and the return address are pushed onto the stack when a function is called; returning from the function call pops those items off the stack.
Heap segment  - all dynamic allocations happens here
Data segment  - stores initialized global and static variables
Text segment  - stores constants, read-only variables, jump tables
http://www.geeksforgeeks.org/memory-layout-of-c-program/

Count smaller elements on the right: (AVL Tree)
http://www.geeksforgeeks.org/count-smaller-elements-on-right-side/

Topological sorting, IntroSort and IntroSelect

Multiple cores process means multiple cores on a single IC. Depending on their architecture, they might share caches (ex: each process has its own L1 cache but L2 & above are shared between cores).
So, Multi core can run multiple instructions but not multiple processes simultaneously.

Function Pointers => http://www.geeksforgeeks.org/function-pointer-in-c/
using function pointers as compare fn for maps.
EX:
  bool fncomp (char lhs, char rhs) { return lhs<rhs; }

  bool(*fn_pt)(char,char) = fncomp;
  std::map<char,int,bool(*)(char,char)> fifth (fn_pt);

emplace back example: Pb. 16.6 Theory of Equality Pg. 381

Heap implementation with decrease key functionality
http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/

Matrix chain multiplication: https://en.wikipedia.org/wiki/Matrix_chain_multiplication

Bloom filter: https://www.youtube.com/watch?v=-SuTGoFYjZs

Custom Iterator:  http://www.cplusplus.com/reference/iterator/iterator/
                  http://en.cppreference.com/w/cpp/language/operators

Union by rank & path compression: https://www.youtube.com/watch?v=ID00PMy0-vE

A* path finding: https://www.youtube.com/watch?v=KNXfSOx4eEE

Kilo (K)  2^10 = 1,024
Mega (M)  2^20 = 1,048,576
Giga (G)  2^30 = 1,073,741,824
Tera (T)  2^40 = 1,099,511,627,776
Peta (P)  2^50 = 1,125,899,906,842,624

Paxos:  https://www.youtube.com/watch?v=WX4gjowx45E&t=894s
        https://www.youtube.com/watch?v=JEpsBg0AO6o

How do you implement a lock free ready-modify-update mechanism in a multithreaded system ?
Ans.  You use load-link and store-conditional (LL/SC) are a pair of instructions used in multithreading to achieve synchronization.
      Load link will retrieve the value from the memory location and the subsequent store will store/update the a new value, only if the no updates have occurred to the location since the load-link operation.

class HashTuple
{
    size_t operator()(const tuple<int, int, int> &t) const
    {  return hash<int>()(get<0>(t)) ^ hash<int>()(get<1>(t)) ^ hash<int>()(get<2>(t));  }
};
unordered_set<tuple<int, int, int>, HashTuple> cache


unordered_map<string, int> dist;
auto cmp = [&dist] (const string& lhs, const string& rhs) -> bool { return dist[lhs] > dist[rhs]; };
priority_queue<string, vector<string>, decltype(cmp)> Q(cmp);


class pairHash
{
public:
    size_t operator() (const pair<int, int>& ob)
    {
        size_t l = hash<int>()(ob.first);
        size_t r = hash<int>()(ob.second);

        return l + 0x9e3779b9 + (r << 6) + (r >> 2);
    }
};
unordered_map< pair<int, int>, int, pairHash > mp;      // key type, mapped-value type, hash function

Minimum spanning Tree
1. Prims      => http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
2. Kruskals   => http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
