#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
using namespace std;

/* Image Compression  15.20  Pg. 127
Implement a cutpoint selection to minimize the number of nodes in a 2d tree representing a imgae    */

const vector<vector<int>> image;

class Point
{
public:
    int x, y;

    Point(int i, int j) : x(i), y(i) {}

    const bool operator>(const Point &that) const
    {   return (x > that.x || y > that.y);    }

    const bool operator==(const Point &that) const
    {   return (x == that.x && y == that.y);    }
};

class HashPoint
{
public:
    const size_t operator()(const Point &p) const
    {   return hash<int>()(p.x) ^ hash<int>()(p.y); }
};

class TreeNode
{
public:
    int n;          // No. of nodes in this subtree including itself

    Point ll, ur;   // Lower-Left, Upper-Right

    vector<TreeNode*> children;
};

bool isMonochromatic(vector<vector<int>> &image_sum, Point ll, Point ur)
{
    int pixel_sum = image_sum[ur.x][ur.y];

    if (ll.x >= 1)
        pixel_sum -= image_sum[ll.x-1][ur.y];

    if (ll.y >= 1)
        pixel_sum -= image_sum[ur.x][ll.y-1];

    if (ll.x >=1 && ll.y >=1)
        pixel_sum += image_sum[ll.x-1][ll.y-1];

    return pixel_sum == 0 ||                            // totally white
           pixel_sum == (ur.x-ll.x+1)*(ur.y-ll.y+1);    // tottaly black
}

TreeNode* Helper(vector<vector<int>> &image_sum, Point &ll, Point &ur, unordered_map<Point, unordered_map<Point, TreeNode*> > &t)
{
    if (ll>ur)
        return NULL;

    if (t[ll].find(ur) == t.end())
    {
        if (isMonochromatic(image_sum, ll, ur))
        {
            TreeNode *p = new TreeNode(1, ll, ur);
            t[ll][ur] = p;
        }
        else
        {
            TreeNode *p = new TreeNode(numeric_limits<int>::max(), ll, ur);

            for (int i=ll.x; i<=ur.x+1; i++)
            {
                for (int j=ll.y; j<=ur.y+1; j++)
                {
                    if ((i!=ll.x && i!=ur.x+1) || (j!=ll.y && j!=ur.y+1))
                    {
                        vector<TreeNode*> children = {
                            Helper(image_sum, ll,             Point(i-1, j-1),  t),
                            Helper(image_sum, Point(ll.x, j), Point(i-1, ur.y), t),
                            Helper(image_sum, Point(i, j),    ur,               t),
                            Helper(image_sum, Point(i, ll.y), Point(ur.x, j-1), t)
                        }

                        int node_num = 1;
                        for (int k = 0; k<4; k++)
                        {
                            node_num += children[k]->n;

                            if (children[k]->n == 0)
                                children[k] = NULL;
                        }

                        if (node_num < p->n)
                        {
                            p->n = node_num;
                            p->children = children;
                        }
                    }
                }
            }

            t[ll][ur] = p;
        }
    }

    return t[ll][ur];
}

TreeNode* calculate_optimal_2D_tree()
{
    vector<vector<int>> image_sum(image);

    for (int i=0; i<image.size(); i++)
    {
        partial_sum(image_sum[i].cbegin(), image_sum[i].cend(), image_sum[i].begin());

        for (int j=0; j<image[i].size(); j++)
            image_sum[i][j] += image_sum[i-1][j];
    }

    unordered_map<Point, unordered_map<Point, TreeNode*>, HashPoint> table; // Map with Points LL, UR and root

    return Helper(image_sum, Point(0,0), Point(image.size()-1, image[0].size()-1), table);
}
