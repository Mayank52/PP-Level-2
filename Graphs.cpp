#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

// 200. Number of Islands
void dfs(vector<vector<char>> &grid, int sr, int sc)
{
    grid[sr][sc] = '0';

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == '1')
        {
            dfs(grid, x, y);
        }
    }
}
int numIslands(vector<vector<char>> &grid)
{
    int count = 0;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '1')
            {
                count++;
                dfs(grid, i, j);
            }
        }
    }

    return count;
}

// 860 · Number of Distinct Islands (LintCode)
/*
Approach:
Same as Number of Islands.
During DFS, keep the path as {'R', 'L', 'D', 'U'}
for right, left, down, up directions.

Also add another character like '$' to indicate that you backtracked.
If you dont add something while backtracking, then mirror images will get the same ans.
Then the number of these unique paths is the number of distinct islands

For Eg: 
1 1 0 0 0
1 0 0 0 0
0 0 0 1 1
0 0 0 0 1

Here you will get two distinct islands: R$B$$ and RB$$
Without adding $ you will get RB for both

*/
void dfs(vector<vector<int>> &grid, int sr, int sc, string &path)
{
    grid[sr][sc] = 0;

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    char pathDir[4] = {'R', 'L', 'D', 'U'};

    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 1)
        {
            path += pathDir[d];
            dfs(grid, x, y, path);
        }
    }

    path += '$';
}
int numberofDistinctIslands(vector<vector<int>> &grid)
{
    set<string> islands;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                string path = "";
                dfs(grid, i, j, path);
                islands.insert(path);
            }
        }
    }

    return islands.size();
}

// 1020. Number of Enclaves
/*
Approach:
For all 1s on the edges mark their islands.
Then count the remaining 1s in the grid.
*/
void dfs(vector<vector<int>> &grid, int sr, int sc)
{
    grid[sr][sc] = 0;

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 1)
        {
            dfs(grid, x, y);
        }
    }
}
int numEnclaves(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    //mark the 1s connected to islands on edges
    for (int j = 0; j < m; j++)
    {
        if (grid[0][j] == 1)
            dfs(grid, 0, j);
        if (grid[n - 1][j] == 1)
            dfs(grid, n - 1, j);
    }
    for (int i = 0; i < n; i++)
    {
        if (grid[i][0] == 1)
            dfs(grid, i, 0);
        if (grid[i][m - 1] == 1)
            dfs(grid, i, m - 1);
    }

    //count the remaining 1s
    int count = 0;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
                count++;
        }
    }

    return count;
}

// 994. Rotting Oranges
int orangesRotting(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    list<vector<int>> que;
    int freshOranges = 0;

    //push all rotten oranges initially into queue, and count fresh oranges
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 2)
                que.push_back({i, j});
            else if (grid[i][j] == 1)
                freshOranges++;
        }
    }

    // if no fresh oranges in grid return 0
    if (freshOranges == 0)
        return 0;

    //use BFS to get the minimum time
    int time = -1;
    while (que.size() != 0)
    {
        int size = que.size();

        while (size-- > 0)
        {
            vector<int> rpair = que.front();
            que.pop_front();

            int sr = rpair[0];
            int sc = rpair[1];

            int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (int d = 0; d < 4; d++)
            {
                int x = sr + dir[d][0];
                int y = sc + dir[d][1];

                if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 1)
                {
                    grid[x][y] = 2;
                    freshOranges--;
                    que.push_back({x, y});
                }
            }
        }

        time++;
    }

    return freshOranges == 0 ? time : -1;
}

// 815. Bus Routes
int numBusesToDestination(vector<vector<int>> &routes, int source, int target)
{
    if (source == target)
        return 0;

    // make a map of {stop : buses that go to that stop}
    // keep a visited for buses, and one for stops
    unordered_map<int, vector<int>> mp;
    vector<bool> busVis(routes.size());
    unordered_map<int, int> stopVis;

    for (int i = 0; i < routes.size(); i++)
    {
        for (int stop : routes[i])
        {
            mp[stop].push_back(i);
        }
    }

    list<int> que;
    que.push_back(source);
    stopVis[source] = true;
    int busCount = 0;

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rstop = que.front();
            que.pop_front();

            // for all buses for this stop
            for (int bus : mp[rstop])
            {
                if (!busVis[bus])
                {
                    busVis[bus] = true;
                    // add the stops you can go to with this bus to the queue
                    for (int stop : routes[bus])
                    {
                        if (stop == target)
                            return busCount + 1;

                        if (!stopVis[stop])
                        {
                            stopVis[stop] = true;
                            que.push_back(stop);
                        }
                    }
                }
            }
        }

        busCount++;
    }

    return -1;
}

// 785. Is Graph Bipartite?
bool isBipartite(vector<vector<int>> &graph)
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}