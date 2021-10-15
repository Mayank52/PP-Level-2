#include <bits/stdc++.h>

using namespace std;

// 2013. Detect Squares
/*
Approach:
We maintain a map of all y coords for each x coord
And a count map with count of each x,y point

Now, to count,
p1 = given x,y
p2 = all y points with same x as p1

Using these p1, p2, we can get p3, p4
the length of side of square = len = y2 - y1

So, p3 = x1 + len, y1
and p4 = x2 + len, y2


Eg:
We have a point

A = .

For all points with same x

So, we get a side of square

            |A
            |
            |
            |
            |B

Now, just for each p1, p2, we get p3, p4 for both left and right sides
So, right side
 A|          |
  |          |
  |          |
 B|          |

  and,left side

  |          |A
  |          |
  |          |
  |          |B


*/
class DetectSquares
{
public:
    unordered_map<int, unordered_set<int>> xymap;
    map<pair<int, int>, int> countmap;

    DetectSquares()
    {
    }

    void add(vector<int> point)
    {
        int x = point[0];
        int y = point[1];

        xymap[x].insert(y);
        countmap[{x, y}]++;
    }

    int count(vector<int> point)
    {
        int x0 = point[0], y0 = point[1];
        int res = 0;

        // for each point with same x axis
        for (int y1 : xymap[x0])
        {
            // if that point is same then skip
            if (y1 == y0)
                continue;

            int x1 = x0;
            int len = abs(y1 - y0);

            res += countmap[{x1, y1}] * countmap[{x0 + len, y0}] * countmap[{x1 + len, y1}]; // right side
            res += countmap[{x1, y1}] * countmap[{x0 - len, y0}] * countmap[{x1 - len, y1}]; // left side
        }

        return res;
    }
};

// 1881. Maximum Value after Insertion
/*
Approach: O(n)
If n is +ve then insert x just before the first digit < x from left
Eg: n = 5421, x = 3
Then ans = 54321
If n is -ve then insert x just before the first digit > x from left
Eg: n = -5421, x = 3
Then ans = -35421

*/
string maxValue(string n, int x)
{
    string res = n + to_string(x);

    bool isNeg = n[0] == '-';

    for (int i = 0; i < n.size(); i++)
    {
        if (isNeg && i > 0 && n[i] - '0' > x)
        {
            res = n.substr(0, i) + to_string(x) + n.substr(i);
            break;
        }
        else if (!isNeg && n[i] - '0' < x)
        {
            res = n.substr(0, i) + to_string(x) + n.substr(i);
            break;
        }
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
