#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <limits.h>
#define pair pair<int, int>

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
bool isBipartite(vector<vector<int>> &graph, int src, vector<int> &vis)
{
    list<vector<int>> que; //{node, color}

    que.push_back({src, 1}); //color: 0 or 1
    vis[src] = 1;

    while (que.size() != 0)
    {
        vector<int> rnode = que.front();
        que.pop_front();

        int u = rnode[0];
        int color = rnode[1];

        for (int v : graph[u])
        {
            if (vis[v] != -1)
            {
                if (vis[v] == color)
                    return false;
            }
            else
            {
                int newColor = (color + 1) % 2;
                vis[v] = newColor;
                que.push_back({v, newColor});
            }
        }
    }

    return true;
}
bool isBipartite(vector<vector<int>> &graph)
{
    vector<int> vis(graph.size(), -1);
    for (int i = 0; i < graph.size(); i++)
    {
        if (vis[i] == -1)
        {
            if (!isBipartite(graph, i, vis))
                return false;
        }
    }

    return true;
}

// MST - Minimum Spanning Tree (Prims Algorithm) (SPOJ)
long long primsAlgo(vector<vector<pair>> &graph)
{
    long long ans = 0;

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<bool> vis(graph.size());

    pq.push({0, 1}); //{weight, node}

    while (pq.size() > 0)
    {
        vector<int> rnode = pq.top();
        pq.pop();

        int u = rnode[1];
        int w = rnode[0];

        if (vis[u])
            continue;

        vis[u] = true;
        ans += w;

        for (pair v : graph[u])
        {
            if (!vis[v.first])
                pq.push({v.second, v.first});
        }
    }

    return ans;
}
void mst()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair>> graph(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    cout << primsAlgo(graph) << endl;
}

// 1584. Min Cost to Connect All Points
int minCostConnectPoints(vector<vector<int>> &points)
{
    int count = points.size();
    int ans = 0;

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<bool> vis(points.size());

    pq.push({0, 0}); //{weight, node}

    while (pq.size() > 0)
    {
        vector<int> rnode = pq.top();
        pq.pop();

        int u = rnode[1];
        int w = rnode[0];

        //if already visited, then skip current node
        if (vis[u])
            continue;

        //mark visited, and add weight to ans
        vis[u] = true;
        ans += w;

        //decrease remaining edge count
        count--;
        if (count == 0)
            return ans;

        // for this point, add closest point into pq
        for (int v = 0; v < points.size(); v++)
        {
            if (!vis[v])
            {
                int w = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                pq.push({w, v});
            }
        }
    }

    return ans;
}

// 778. Swim in Rising Water
int swimInWater(vector<vector<int>> &grid)
{
    int n = grid.size();

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq; // {max, i, j}
    vector<vector<bool>> vis(n, vector<bool>(n));

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    pq.push({grid[0][0], 0, 0});
    vis[0][0] = true;

    while (pq.size() > 0)
    {
        vector<int> rnode = pq.top();
        pq.pop();

        int w = rnode[0];
        int i = rnode[1];
        int j = rnode[2];

        for (int d = 0; d < 4; d++)
        {
            int x = i + dir[d][0];
            int y = j + dir[d][1];

            if (x == n - 1 && y == n - 1)
                return max(grid[x][y], w);

            if (x >= 0 && y >= 0 && x < n && y < n && !vis[x][y])
            {
                pq.push({max(grid[x][y], w), x, y});
                vis[x][y] = true;
            }
        }
    }

    return -1;
}

// 542. 01 Matrix
/*
Approach: BFS
Add all zeroes into queue.
Then use BFS
For each element popped from queue check its adjacent elements
If it is 1 then its distance will be current cell's distance + 1
Then add it into queue
*/
vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
{
    int n = mat.size();
    int m = mat[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m));
    vector<vector<int>> res(n, vector<int>(m));
    queue<vector<int>> que;

    // push all 0s into que, and their ans in distance array will be 0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 0)
            {
                vis[i][j] = true;
                que.push({i, j, 0});
            }
        }
    }

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (que.size() > 0)
    {
        vector<int> rnode = que.front();
        que.pop();

        //for each element in queue distance for its adjacent 1 will be its distance + 1
        for (int d = 0; d < 4; d++)
        {
            int x = rnode[0] + dir[d][0];
            int y = rnode[1] + dir[d][1];

            if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y] && mat[x][y] == 1)
            {
                vis[x][y] = true;
                res[x][y] = rnode[2] + 1;
                que.push({x, y, rnode[2] + 1});
            }
        }
    }

    return res;
}

// 1162. As Far from Land as Possible
/*
Approach:
Similar to 01 matrix
Push all 1s into queue with distance 0
Now for the top of queue push all its adjacent 0s into queue
And ans is the last level in BFS as it will be the maximum distance from nearest 1
*/
int maxDistance(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    list<vector<int>> que; //{distance, i, j}

    // push all 1s into que with 0 distance
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
                que.push_back({i, j});
        }
    }

    // no water or land, return -1
    if (que.size() == 0 || que.size() == n * m)
        return -1;

    int dist = 0;
    while (que.size() > 0)
    {
        int size = que.size();

        while (size-- > 0)
        {
            vector<int> rnode = que.front();
            que.pop_front();

            int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (int d = 0; d < 4; d++)
            {
                int x = rnode[0] + dir[d][0];
                int y = rnode[1] + dir[d][1];

                if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 0)
                {
                    grid[x][y] = 1;
                    que.push_back({x, y});
                }
            }
        }

        dist++;
    }

    return dist - 1;
}

//Bellman Ford
void bellmanFordAlgo(vector<vector<int>> graph)
{
}

// Strongly Connected Components (Kosaraju's Algo) (GFG)
stack<int> st;
void dfs(vector<vector<int>> &graph, int src, vector<bool> &vis)
{
    vis[src] = true;

    for (int v : graph[src])
    {
        if (!vis[v])
            dfs(graph, v, vis);
    }

    st.push(src);
}
int kosaraju(int V, vector<int> adj[])
{
    //code here
    int n = V;
    vector<vector<int>> graph(n);
    vector<bool> vis(n);

    for (int i = 0; i < n; i++)
    {
        for (int v : adj[i])
        {
            graph[i].push_back(v);
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs(graph, i, vis);
    }

    vector<vector<int>> revGraph(n);
    vector<bool> nVis(n);
    for (int i = 0; i < n; i++)
    {
        for (int v : adj[i])
        {
            revGraph[v].push_back(i);
        }
    }

    int count = 0;
    while (st.size() > 0)
    {
        int src = st.top();
        st.pop();

        if (!nVis[src])
        {
            dfs(revGraph, src, nVis);
            count++;
        }
    }

    return count;
}

// Mother Vertex
/*
Approach:
1. Use Step 1 of Kosaraju Algo to build the stack
2. Now the top element of stack can be the mother vertex or their is no mother vertex
3. Verify if top element is mother vertex
*/
stack<int> st;
int count = 0;
void dfs(vector<int> adj[], int src, vector<bool> &vis)
{
    count++;
    vis[src] = true;

    for (int v : adj[src])
    {
        if (!vis[v])
            dfs(adj, v, vis);
    }

    st.push(src);
}
int findMotherVertex(int V, vector<int> adj[])
{
    //build the stack
    vector<bool> vis(V);
    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
            dfs(adj, i, vis);
    }

    //top of stack can be a mother vertex
    int vtx = st.top();

    //verify
    count = 0;
    vis.assign(V, false);
    dfs(adj, vtx, vis);

    return count == V ? vtx : -1;
}

// 1034. Coloring A Border
/*
Approach:
Use DFS
Make 4 calls to each adjacent cell from each cell
Count the number of adjacent cells with same color
If count < 4, then it is on border, so change its color

Keep a visited array, while checking adjacent cells,
1. If it has already been visited, then just increase the count because it must have the same color
2. If it has same color, and not been visited,then call for that cell, and increase count

We cannot just check the color of adjacent cell, as we are changing the color of border cells
So, they will give the wrong answer.
*/
void dfs(vector<vector<int>> &grid, int sr, int sc, int color, vector<vector<bool>> &vis)
{
    int n = grid.size();
    int m = grid[0].size();

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vis[sr][sc] = true;
    int count = 0;

    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x < n && y < m)
        {
            //if it already been visited, then just increase the count
            if (vis[x][y])
                count++;

            //if it has same color, then go to that cell
            else if (grid[x][y] == grid[sr][sc])
            {
                dfs(grid, x, y, color, vis);
                count++;
            }
        }
    }

    // if count < 4, this cell is on border
    if (count < 4)
    {
        grid[sr][sc] = color;
    }
}
vector<vector<int>> colorBorder(vector<vector<int>> &grid, int r0, int c0, int color)
{
    vector<vector<bool>> vis;
    dfs(grid, r0, c0, color, vis);

    return grid;
}

// 934. Shortest Bridge
int shortestBridge(vector<vector<int>> &grid)
{
}

// Topological sort (Kahn's Algo) (GFG)
vector<int> topoSort(int V, vector<int> adj[])
{
    int n = V;
    vector<int> indegree(n, 0);
    vector<int> res;

    for (int i = 0; i < n; i++)
        for (int v : adj[i])
            indegree[v]++;

    list<int> que;
    for (int i = 0; i < indegree.size(); i++)
        if (indegree[i] == 0)
            que.push_back(i);

    while (que.size() > 0)
    {
        int rnode = que.front();
        que.pop_front();

        res.push_back(rnode);

        for (int v : adj[rnode])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                que.push_back(v);
            }
        }
    }

    return res;
}

// 210. Course Schedule II
vector<int> kahnAlgo(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> indegree(n, 0);
    vector<int> res;

    for (int i = 0; i < n; i++)
        for (int v : graph[i])
            indegree[v]++;

    list<int> que;
    for (int i = 0; i < indegree.size(); i++)
        if (indegree[i] == 0)
            que.push_back(i);

    while (que.size() > 0)
    {
        int rnode = que.front();
        que.pop_front();

        res.push_back(rnode);

        for (int v : graph[rnode])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                que.push_back(v);
            }
        }
    }

    return res;
}
vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{
    int n = numCourses;

    vector<vector<int>> graph(n);
    for (int i = 0; i < prerequisites.size(); i++)
    {
        int u = prerequisites[i][1];
        int v = prerequisites[i][0];
        graph[u].push_back(v);
    }

    vector<int> res = kahnAlgo(graph);

    if (res.size() != n)
        return {};
    return res;
}

// 207. Course Schedule
vector<int> kahnAlgo(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> indegree(n, 0);
    vector<int> res;

    for (int i = 0; i < n; i++)
        for (int v : graph[i])
            indegree[v]++;

    list<int> que;
    for (int i = 0; i < indegree.size(); i++)
        if (indegree[i] == 0)
            que.push_back(i);

    while (que.size() > 0)
    {
        int rnode = que.front();
        que.pop_front();

        res.push_back(rnode);

        for (int v : graph[rnode])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                que.push_back(v);
            }
        }
    }

    return res;
}
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    int n = numCourses;

    vector<vector<int>> graph(n);
    for (int i = 0; i < prerequisites.size(); i++)
    {
        int u = prerequisites[i][1];
        int v = prerequisites[i][0];
        graph[u].push_back(v);
    }

    vector<int> res = kahnAlgo(graph);

    return res.size() == n;
}

// 892 · Alien Dictionary (Lintcode)
string alienOrder(vector<string> &words)
{
    // Write your code here
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mst();
    return 0;
}