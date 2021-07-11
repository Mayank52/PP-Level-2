#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <limits.h>
#include <algorithm>
// #define pair pair<int, int>

using namespace std;

// Extra Questions==============================================================
// 997. Find the Town Judge
/*
Approach: 
Find the indegree and outdegree of each node
The node with indegree == n-1 && outdegree == 0 is the answer

We dont need outdegree seperately, we can just +1 and -1 in indegree itself
*/
int findJudge(int n, vector<vector<int>> &trust)
{
    vector<int> indegree(n + 1);

    for (vector<int> &e : trust)
    {
        indegree[e[1]]++;
        indegree[e[0]]--;
    }

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == n - 1)
            return i;
    }

    return -1;
}

// 1557. Minimum Number of Vertices to Reach All Nodes
/*
Approach:
We have to find nodes with indegree = 0
Because they cannot be reached from any other node. So, they must be in the answer
Other nodes with >0 indegree means, they can all be reached from other nodes
*/
vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges)
{
    vector<int> indegree(n);
    vector<int> res;

    for (vector<int> &e : edges)
    {
        indegree[e[1]]++;
    }

    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
            res.push_back(i);
    }

    return res;
}

// 1319. Number of Operations to Make Network Connected
/*
Approach: DSU
Count the number of connected components, redundant edges in graph
Ans = number of components - 1

Eg: To connect 3 different components of a graph you need 3 - 1 = 2 edges

So, redundant edges gives the extra available edges, and if
reduntantEdgeCount >= componentCount - 1
*/
vector<int> par;
int find(int u)
{
    if (par[u] == u)
        return u;
    return par[u] = find(par[u]);
}
int makeConnected(int n, vector<vector<int>> &connections)
{
    par.resize(n);

    // Initially componentCount = no. of nodes
    int redundantEdgeCount = 0, componentCount = n;

    for (int i = 0; i < n; i++)
        par[i] = i;

    for (vector<int> &e : connections)
    {
        int u = e[0];
        int v = e[1];

        int p1 = find(e[0]);
        int p2 = find(e[1]);

        // increase redundant edge count
        if (p1 == p2)
        {
            redundantEdgeCount++;
        }
        // merge two sets, reduce component count
        else
        {
            par[p1] = p2;
            componentCount--;
        }
    }

    if (redundantEdgeCount >= componentCount - 1)
        return componentCount - 1;
    else
        return -1;
}

// 1514. Path with Maximum Probability
/*
Approach: Dijsktra's Algo
*/
double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end)
{
    vector<double> res(n);
    vector<vector<vector<double>>> graph(n);
    vector<bool> vis(n);

    for (int i = 0; i < edges.size(); i++)
    {
        double u = edges[i][0];
        double v = edges[i][1];
        double w = succProb[i];

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    priority_queue<vector<double>, vector<vector<double>>> pq;
    pq.push({1.0, start * 1.0});

    while (pq.size() > 0)
    {
        vector<double> rnode = pq.top();
        pq.pop();

        double u = rnode[1];
        double p = rnode[0];

        res[u] = max(res[u], p);
        vis[u] = true;

        for (vector<double> &e : graph[u])
        {
            if (!vis[e[0]])
            {
                pq.push({e[1] * p, e[0]});
            }
        }
    }

    return res[end];
}

// 1466. Reorder Routes to Make All Paths Lead to the City Zero
/*
Approach: DFS
Make a adjacency list, and mark the direction for each edge
0-> towards node ,1-> away from node
Now since we have to make each path reach 0, and the graph is a tree
So, just consider 0 as root, and in dfs from 0 
count all edges where the edge points away from parent towards child
*/
int count = 0;
void dfs(vector<vector<pair>> &graph, int src, vector<bool> &vis)
{
    vis[src] = true;

    for (pair &e : graph[src])
    {
        int v = e.first;
        int dir = e.second;
        if (!vis[v])
        {
            if (dir == 1)
                count++;

            dfs(graph, v, vis);
        }
    }
}
int minReorder(int n, vector<vector<int>> &connections)
{
    vector<vector<pair>> graph(n);
    vector<bool> vis(n);

    for (vector<int> &e : connections)
    {
        int u = e[0];
        int v = e[1];

        graph[u].push_back({v, 1});
        graph[v].push_back({u, 0});
    }

    dfs(graph, 0, vis);

    return count;
}

// 947. Most Stones Removed with Same Row or Column
/*
Approach : Union Find
Use the coords x, y as two different nodes, and use union find
To avoid overlap between equal values of row, col like {0, 1}, and {1, 0}
use x and ~y

If we use the just use x and y in parent map, then in
{{0, 1}, {1, 0}}
the values of row and col will overlap, and it will give answer 1,
but ans is 0, as no stone can be removed.

*/
unordered_map<int, int> par;
int count = 0;
int find(int u)
{
    // if not present in map, then add to map and increase set count
    if (par.find(u) == par.end())
    {
        count++;
        return par[u] = u;
    }

    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
int removeStones(vector<vector<int>> &stones)
{
    int n = stones.size();

    for (vector<int> &coords : stones)
    {
        int u = coords[0];
        int v = ~coords[1];

        //find parents of both row and col
        int p1 = find(u);
        int p2 = find(v);

        // merge two sets, decrease count
        if (p1 != p2)
        {
            par[p1] = p2;
            count--;
        }
    }

    return n - count;
}

// PP List Questions================================================================
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

// Negative weight cycle (GFG) (Bellman Ford Algo)
/*
Approach:
Bellman Ford algo
*/
int isNegativeWeightCycle(int n, vector<vector<int>> edges)
{
    // Code here
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    //make distance array for all nodes by iterating over all edges V-1 times
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if (dist[u] == INT_MAX)
                continue;

            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check if negative cycle is present by iterating once more
    for (int j = 0; j < edges.size(); j++)
    {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];

        if (dist[u] == INT_MAX)
            continue;

        // if the distance is < distance already in the distance array, then -ve weight cycle is present
        if (dist[u] + w < dist[v])
            return 1;
    }

    return 0;
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
/*
Approach: BFS
Mark 1 island with a color, like 2
While marking using DFS, add its border into a queue

Now, use this queue, and apply BFS
Check 4 directions for each cell, 
    if it is zero, push into queue and mark visited
    if it is 1, you have reached the second island
    
Keep a level count of the BFS
When you reach the second island, that level is the answer
*/
queue<vector<int>> que;
void dfs(vector<vector<int>> &grid, int sr, int sc)
{
    int n = grid.size();
    int m = grid[0].size();

    grid[sr][sc] = 2;

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int count = 0;

    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 1)
        {
            dfs(grid, x, y);
            count++;
        }
    }

    if (count < 4)
        que.push({sr, sc});
}
int shortestBridge(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    // mark one island as 2, and store its boundary in a queue
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                dfs(grid, i, j);
                flag = true;
                break;
            }
        }

        if (flag)
            break;
    }

    // Use BFS, until you reach a 1, then the level of BFS is the answer
    int lvl = 0;
    while (que.size() > 0)
    {
        int size = que.size();

        while (size-- > 0)
        {
            vector<int> rcell = que.front();
            que.pop();

            int currColor = rcell[2];
            int sr = rcell[0];
            int sc = rcell[1];

            int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

            for (int d = 0; d < 4; d++)
            {
                int x = sr + dir[d][0];
                int y = sc + dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < m)
                {
                    if (grid[x][y] == 0)
                    {
                        que.push({x, y});
                        grid[x][y] = 2;
                    }
                    else if (grid[x][y] == 1)
                        return lvl;
                }
            }
        }

        lvl++;
    }

    return 0;
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
/*
Approach: Kahn's Algo (Topological Sort)
For the words array, build a directed graph
Then use kahn algo, to find the answer
*/
string alienOrder(vector<string> &words)
{
    int n = words.size();

    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> indegree;

    // initialize indegree for all nodes
    for (int i = 0; i < n; i++)
    {
        for (char ch : words[i])
            indegree[ch] = 0;
    }

    // build the graph
    for (int i = 0; i < n - 1; i++)
    {
        string word1 = words[i];
        string word2 = words[i + 1];

        int len = min(word1.size(), word2.size());
        int idx = 0;
        bool flag = false;
        while (idx < len)
        {
            char u = word1[idx];
            char v = word2[idx];
            if (u != v)
            {
                indegree[v]++;
                graph[u].insert(v);
                flag = true;
                break;
            }

            idx++;
        }

        // if the current word is before next word, but nothing in it is smaller then next word
        // and its length is also not less, then dictionary is invalid
        if (idx == len && word1.size() > word2.size())
            return "";
    }

    //Kahn's Algo to find answer

    // Lintcode wants the lexicographically smaller answer from possible answers
    // So, PQ is used, otherwise normal queue can be used

    priority_queue<char, vector<char>, greater<int>> que;
    string res = "";
    for (auto node : indegree)
    {
        if (node.second == 0)
        {
            que.push(node.first);
        }
    }

    while (que.size() > 0)
    {
        char rnode = que.top();
        que.pop();

        res += rnode;

        for (char v : graph[rnode])
        {
            if (indegree[v] > 0)
            {
                indegree[v]--;
                if (indegree[v] == 0)
                    que.push(v);
            }
        }
    }

    // if the res does not include all nodes, then there is a cycle
    // so return ""
    return res.size() == indegree.size() ? res : "";
}

// Disjoint Set Union (DSU)
vector<int> par;
vector<int> size;

int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}

void merge(int x, int y)
{
    int p1 = find(x);
    int p2 = find(y);

    if (p1 != p2)
    {
        if (size[p1] > size[p2])
        {
            par[p2] = p1;
            size[p1] += size[p2];
        }
        else
        {
            par[p1] = p2;
            size[p2] += size[p1];
        }
    }
}

// 434 · Number of Islands II (Lintcode)
struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
vector<int> par;
vector<int> size;
int count = 0;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(int x, int y)
{
    int p1 = find(x);
    int p2 = find(y);

    if (p1 != p2)
    {
        count--;
        if (size[p1] > size[p2])
        {
            par[p2] = p1;
            size[p1]++;
        }
        else
        {
            par[p1] = p2;
            size[p2]++;
        }
    }
}
vector<int> numIslands2(int n, int m, vector<Point> &operators)
{
    // write your code here
    par.resize(n * m, -1);
    size.resize(n * m);
    count = 0;

    vector<int> res;

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (Point pt : operators)
    {
        int i = pt.x;
        int j = pt.y;

        int cell = i * m + j;

        if (par[cell] != -1)
        {
            res.push_back(count);
            continue;
        }

        // initialize parent, size for the this cell and increase count by 1
        par[cell] = cell;
        size[cell] = 1;
        count++;

        for (int d = 0; d < 4; d++)
        {
            int x = i + dir[d][0];
            int y = j + dir[d][1];

            int newCell = x * m + y;

            if (x >= 0 && y >= 0 && x < n && y < m && par[newCell] != -1)
            {
                merge(cell, newCell);
            }
        }

        res.push_back(count);
    }

    return res;
}

// 959. Regions Cut By Slashes
vector<int> par;
vector<int> size;
int count = 0;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(int x, int y)
{
    int p1 = find(x);
    int p2 = find(y);

    if (p1 != p2)
    {
        if (size[p1] >= size[p2])
        {
            par[p2] = p1;
            size[p1] += size[p2];
        }
        else
        {
            par[p1] = p2;
            size[p2] += size[p1];
        }
    }
    else
    {
        count++;
    }
}
int regionsBySlashes(vector<string> &grid)
{
    int n = grid.size();
    int dots = n + 1;

    par.resize(dots * dots);
    size.resize(dots * dots, 1);

    for (int i = 0; i < par.size(); i++)
        par[i] = i;

    // put all points on border in one set
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0 || i == n || j == n)
            {
                int cell = i * dots + j;
                if (cell != 0)
                    merge(0, cell);
            }
        }
    }

    // initial count is 1
    count = 1;

    // get the count for the slashes added
    for (int i = 0; i < grid.size(); i++)
    {

        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '/')
            {
                int cell1 = (i + 1) * dots + j;
                int cell2 = i * dots + (j + 1);

                merge(cell1, cell2);
            }

            else if (grid[i][j] == '\\')
            {
                int cell1 = i * dots + j;
                int cell2 = (i + 1) * dots + (j + 1);

                merge(cell1, cell2);
            }
        }
    }

    return count;
}

// 855 · Sentence Similarity II
/*
Approach:
Use DSU
First make the sets using the pairs
Now for each sentence, check if both words belong to same set
If they dont belong to same set, return false
Else return true
*/
unordered_map<string, string> par;
unordered_map<string, int> size;
string find(string &u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(string &u, string &v)
{
    string p1 = find(u);
    string p2 = find(v);

    if (p1 != p2)
    {
        if (size[p1] < size[p2])
        {
            par[p1] = p2;
            size[p2]++;
        }
        else
        {
            par[p2] = p1;
            size[p1]++;
        }
    }
}
bool areSentencesSimilarTwo(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs)
{
    if (words1.size() != words2.size())
        return false;

    for (string &word : words1)
    {
        par[word] = word;
        size[word] = 1;
    }
    for (string &word : words2)
    {
        par[word] = word;
        size[word] = 1;
    }

    for (vector<string> &pr : pairs)
        merge(pr[0], pr[1]);

    for (int i = 0; i < words1.size(); i++)
    {
        string word1 = words1[i];
        string word2 = words2[i];

        if (par[word1] != par[word2])
            return false;
    }

    return true;
}

// 990. Satisfiability of Equality Equations
/*
Approach : DSU
Iterate the equations twice
First make sets using all == equations
Then in second iteration, check if any a!=b equation has same parents for a and b
If they have same parents, then return false
*/
unordered_map<char, char> par;
unordered_map<char, int> size;
char find(char u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(char x, char y)
{
    char p1 = find(x);
    char p2 = find(y);

    if (p1 != p2)
    {
        if (size[p1] > size[p2])
        {
            par[p2] = p1;
            size[p1]++;
        }
        else
        {
            par[p1] = p2;
            size[p2]++;
        }
    }
}
bool equationsPossible(vector<string> &equations)
{
    // make sets using only == equations
    for (string eq : equations)
    {
        char x = eq[0];
        char y = eq[3];
        char equality = eq[1];

        if (par.find(x) == par.end())
        {
            par[x] = x;
            size[x] = 1;
        }
        if (par.find(y) == par.end())
        {
            par[y] = y;
            size[y] = 1;
        }

        if (equality == '=')
        {
            merge(x, y);
        }
    }

    // check for != equations
    for (string eq : equations)
    {
        char x = eq[0];
        char y = eq[3];
        char equality = eq[1];

        if (equality == '!')
        {
            char p1 = find(x);
            char p2 = find(y);

            if (p1 == p2)
                return false;
        }
    }

    return true;
}

// 399. Evaluate Division
/*
Approach : DFS (Path Finding)
For given equation
a/b = 2.0,
b/c = 3.0

We will consider a, b, c as nodes in graph, and 2.0 and 3.0 as weight of their edges
The graph will be directed and weighted. 
For eg: For a edges u,v with weight w
We will make a edge u-v with weight w
And an edge v-u with weight 1/w

So, each edge u->v represents u/v. So multiplying such edges will be same as 
u/v * v/w * w/x = u/x
So, we can get the answers for the queries by just finding the path in graph
and finding the product of edges on that path.

So weight of 
a-b edge is 2.0 
but weight of b-a edge is 1 / 2.0 = 0.5

So for a query like a/c
We have a graph : a-b-c

For a/c we find a path from a->c in graph and multiply all the weights in that path
So in this it will be a->b->c = 2.0 x 3.0 = 6.0

*/
double dfs(unordered_map<string, vector<pair<string, double>>> &graph, string &src, string &dest, unordered_map<string, bool> &vis)
{
    if (src == dest)
        return 1.0;

    vis[src] = true;

    for (pair<string, double> e : graph[src])
    {
        if (!vis[e.first])
        {
            double ans = dfs(graph, e.first, dest, vis);
            if (ans > 0)
                return ans * e.second;
        }
    }

    return 0;
}
vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
{
    typedef pair<string, double> pair;

    unordered_map<string, vector<pair>> graph;

    // make graph
    for (int i = 0; i < equations.size(); i++)
    {
        string u = equations[i][0];
        string v = equations[i][1];
        double w = values[i];

        graph[u].push_back({v, w});
        graph[v].push_back({u, 1 / w});
    }

    vector<double> res;

    for (vector<string> &query : queries)
    {
        string src = query[0];
        string dest = query[1];

        // if either of the elements are not in graph, return -1
        if (graph.find(src) == graph.end() || graph.find(dest) == graph.end())
        {
            res.push_back(-1.0);
            continue;
        }

        // find the product of edges in the path b/w src->dest
        unordered_map<string, bool> vis;

        double ans = dfs(graph, src, dest, vis);
        if (ans > 0)
            res.push_back(ans);
        else
            res.push_back(-1.0);
    }

    return res;
}

// 684. Redundant Connection
/*
Approach : DSU
For each edge:
    If they have have different parents, then merge
    If same parents, then they both have been merged already, it is a redundant edge
*/
vector<int> par;
vector<int> size;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(int p1, int p2)
{
    if (size[p1] < size[p2])
    {
        par[p1] = p2;
        size[p2] += size[p1];
    }
    else
    {
        par[p2] = p1;
        size[p1] += size[p2];
    }
}
vector<int> findRedundantConnection(vector<vector<int>> &edges)
{
    int n = edges.size() + 1;
    par.resize(n);
    size.resize(n, 1);

    for (int i = 0; i < n; i++)
    {
        par[i] = i;
    }

    vector<int> res(2);

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        int p1 = find(u);
        int p2 = find(v);

        if (p1 == p2)
        {
            res[0] = u;
            res[1] = v;
        }
        else
            merge(p1, p2);
    }

    return res;
}

// 685. Redundant Connection II
vector<int> par;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
bool merge(int u, int v)
{
    int p1 = find(u);
    int p2 = find(v);

    // both in same set -> cycle present
    if (p1 == p2)
        return true;

    // else merge both in same set
    par[p1] = p2;

    return false;
}
vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
{
    int n = edges.size();

    for (int i = 0; i <= n; i++)
    {
        par.push_back(i);
    }

    vector<int> indegree(n + 1, -1);
    int bl1 = -1, bl2 = -1;

    for (int i = 0; i < n; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        if (indegree[v] == -1)
            indegree[v] = i; // indegree is 1, and store the edge making the indegree 1
        else
        {
            bl1 = i;           // blacklist 1 = second edge that causes the indegree 2
            bl2 = indegree[v]; // blackklist 2 = first edge that made indegree 1 initially
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (bl1 == i)
            continue;

        int u = edges[i][0];
        int v = edges[i][1];

        int p1 = find(u);
        int p2 = find(v);

        // check if cycle
        bool hasCycle = merge(u, v);

        // cycle present
        if (hasCycle)
        {
            // if indegree is not 2, then the edge causing the cycle is redundant
            if (bl1 == -1)
                return edges[i];
            // if indegree is 2, then the second edge that was blacklisted is redundant
            // because the first blacklist was already removed
            else
                return edges[bl2];
        }
    }

    // no cycle, then the answer is edge making indegree 2
    return edges[bl1];
}

// 924. Minimize Malware Spread
/*
Approach : Union Find
First use DSU and and make the parent and size array using the given graph
Then iterate over the initial array and make a map of {parent : infected count}
Then iterate over the initial array again and if the infected count of its parent is 1 then update the ans
if its set size is greater , but if the infected count is >1 then removing that vertex wont help.
So, it cant be the answer.

So, we first make the sets
Then we try to find the node with max set size, and it is the only infected node in its set.
If no such node, then removing any node will have the same the effect.
*/
vector<int> par;
vector<int> size;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(int u, int v)
{
    int p1 = find(u);
    int p2 = find(v);

    if (p1 != p2)
    {
        if (size[p1] < size[p2])
        {
            par[p1] = par[p2];
            size[p2] += size[p1];
        }
        else
        {
            par[p2] = par[p1];
            size[p1] += size[p2];
        }
    }
}
int minMalwareSpread(vector<vector<int>> &graph, vector<int> &initial)
{
    int n = graph.size();

    sort(initial.begin(), initial.end());

    for (int i = 0; i < n; i++)
    {
        par.push_back(i);
        size.push_back(1);
    }

    //make the parent and size array
    for (int u = 0; u < graph.size(); u++)
    {
        for (int v = u + 1; v < graph[0].size(); v++)
        {
            if (graph[u][v] == 1)
            {
                merge(u, v);
            }
        }
    }

    // for each infected node, in the map update the parent: infected count
    unordered_map<int, int> mp;

    for (int i = 0; i < initial.size(); i++)
    {
        int p = find(initial[i]);
        mp[p]++;
    }

    // now for each infected node, update the answer
    int ans = initial[0], maxSize = 0;

    for (int i = 0; i < initial.size(); i++)
    {
        int p = find(initial[i]);
        int parSize = size[p];

        // if its set size is greater, and it is the only infected node in its set, then it is the answer
        if (parSize > maxSize && mp[p] == 1)
        {
            maxSize = parSize;
            ans = initial[i];
        }
    }

    return ans;
}

// Kruskal Algo (MST)
// https://www.spoj.com/problems/MST/
vector<int> par;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
long long kruskalAlgo(vector<vector<int>> &edges)
{
    int n = edges.size();

    for (int i = 0; i <= n; i++)
        par.push_back(i);

    // sort edges in increasing order of weight
    sort(edges.begin(), edges.end());

    long long res = 0;

    // use DSU to make the MST
    for (vector<int> &edge : edges)
    {
        int p1 = find(edge[1]);
        int p2 = find(edge[2]);

        // if not a cycle, then include in the MST
        if (p1 != p2)
        {
            par[p1] = p2;
            res += edge[0];
        }
    }

    return res;
}
void mst()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges.push_back({w, u, v});
    }

    cout << kruskalAlgo(edges) << endl;
}

// 1168. Optimize Water Distribution in a Village (Premium, not available to submit anywhere)
/*
Approach: MST
Consider the well as a seperate node, and add edges to all other nodes using cost as weight
Then find the MST using prims or Kruskal
*/
void optimizeWater(vector<int> &wells, vector<int> &pipes)
{
}

// Articulation Points(Nodes) and Bridges(Edges)
// https://www.spoj.com/problems/SUBMERGE/ (SPOJ)
/*
Approach: Articulation Points
*/
vector<int> par;
vector<int> disc;
vector<int> low;
vector<bool> ap;
vector<bool> vis;
int discTime = 0;
int srcCount = 0;
void dfs(vector<vector<int>> &graph, int src)
{
    low[src] = discTime;
    disc[src] = discTime;
    vis[src] = true;

    discTime++;

    for (int v : graph[src])
    {
        // if the neighbor is my parent
        if (par[src] == v)
            continue;
        // if neighor visited already
        else if (vis[v])
            low[src] = min(low[src], disc[v]);
        // if not visited
        else
        {
            // mark this node as neighbor's parent
            par[v] = src;

            // call for it
            dfs(graph, v);

            if (par[src] == 0) // actual source
            {
                srcCount++;
                // if source has been reached more than 1 time, then it is also an Articulation point
                if (srcCount >= 2)
                    ap[src] = true;
            }
            // check if current node is an Articulation Point
            else if (low[v] >= disc[src])
                ap[src] = true;

            low[src] = min(low[src], low[v]);
        }
    }
}
void articulationPoints(vector<vector<int>> &graph, int n)
{
    par.assign(n + 1, 0);
    disc.assign(n + 1, 0);
    low.assign(n + 1, 0);
    ap.assign(n + 1, 0);
    vis.assign(n + 1, 0);
    srcCount = 0;
    discTime = 0;

    dfs(graph, 1);
}
void solve()
{
    while (true)
    {
        int n, m;
        cin >> n >> m;

        if (n == 0 && m == 0)
            return;

        vector<vector<int>> graph(n + 1);

        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        articulationPoints(graph, n);

        int res = 0;
        for (int i = 1; i <= n; i++)
        {
            if (ap[i])
            {
                res++;
            }
        }

        cout << res << endl;
    }
}

// 1192. Critical Connections in a Network
/*
Approach: Articulation Bridges
*/
vector<int> par;
vector<int> disc;
vector<int> low;
vector<bool> vis;
vector<vector<int>> res;
int discTime = 0;
int srcCount = 0;
void articulationBridges(vector<vector<int>> &graph, int src)
{
    low[src] = discTime;
    disc[src] = discTime;
    vis[src] = true;

    discTime++;

    for (int v : graph[src])
    {
        // if the neighbor is my parent
        if (par[src] == v)
            continue;
        // if neighor visited already
        else if (vis[v])
            low[src] = min(low[src], disc[v]);
        // if not visited
        else
        {
            // mark this node as neighbor's parent
            par[v] = src;

            // call for it
            articulationBridges(graph, v);

            // check if this edge is Articulation Bridge
            if (low[v] > disc[src])
                res.push_back({src, v});

            low[src] = min(low[src], low[v]);
        }
    }
}
vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
{
    vector<vector<int>> graph(n);
    for (vector<int> &e : connections)
    {
        int u = e[0];
        int v = e[1];

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    par.assign(n, -1);
    disc.assign(n, 0);
    low.assign(n, 0);
    vis.assign(n, 0);
    srcCount = 0;
    discTime = 0;

    articulationBridges(graph, 0);

    return res;
}

// Job Sequencing Problem
/*
Approach 1:
Sort the jobs in decreasing order of profit
Now for each job find the last available day and assign it to this job
And include this job in profit

Approach 2: DSU
We dont use the complete DSU. We only use the find() method and path compression
to get the last available day faster and merge with the parent of previous day always.
Use the parent array to store the last day.
For each Job:
1. Find its last day
2. If last day = 0 i.e. no day is available then dont include it
   Else include this job, and merge its last available day with that day's previous day
   i.e. we merge it with the previous day of its parent, 
   and we always make the parent of previous day as its parent
   This way we can update the last available day.

So, 
find p1 = parent of current deadline
then if p1 > 0 i.e we have a day available
then include this job and
merge p1 with p1 - 1
i.e. p2 = find(p1-1)
and par[p1] = p2

For eg:
Job id      Deadline    Profit
A              4         120
B              1         110
C              3         100
D              4         90
E              5         80
F              5         10

Initially parent array:
0 1 2 3 4 5

Profit = 0

Now for job A
find(4) = 4,    Profit = 120
Merge 4 with parent of 4 - 1 = par[3] = 3
So par[] = 0 1 2 3 3 5

Job B:
find(1) = 1, Profit = 120 + 110
Merge 1 with parent of 1 - 1 = par[0] = 0
par[] = 0 0 2 3 3 5

Job C:
find(3) = 3, Profit = 120 + 110 + 100
Merge 3 with parent of 3 - 1 = par[2] = 2
par[] = 0 0 2 2 3 5

Job D:
p1 = find(4) = 2, Profit = 120 + 110 + 100 + 90
Merge 2 with parent of 2 - 1 = par[0] = 0
par[] = 0 0 0 2 2 5
So, we merge parent of current element i.e. p1 with p1 - 1
This way we can update the last available day.

Job E:
find(5) = 5, Profit = 120 + 110 + 100 + 90 + 80
Merge 5 with parent of 5 - 1 = par[4] = 0
par[] = 0 0 0 2 0 0

*/
struct Job
{
    int id;     // Job Id
    int dead;   // Deadline of job
    int profit; // Profit if job is over before or on deadline
};
// Approach 1: Greedy
vector<int> JobScheduling(Job arr[], int n)
{
    // find the max days available
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        maxDeadline = max(maxDeadline, arr[i].dead);

    vector<int> days(maxDeadline + 1);

    // sort in decresing order of profit
    sort(arr, arr + n, [](Job j1, Job j2)
         { return j1.profit > j2.profit; });

    int totalProfit = 0, jobCount = 0;
    for (int i = 0; i < n; i++)
    {
        int jobid = arr[i].id;
        int deadline = arr[i].dead;
        int profit = arr[i].profit;

        // find any available slot before the current job's deadline, and assign it to this job
        for (int j = deadline; j > 0; j--)
        {
            if (days[j] == 0)
            {
                days[j] = jobid;
                totalProfit += profit;
                jobCount++;
                break;
            }
        }
    }

    return {jobCount, totalProfit};
}

//Approach 2: DSU
vector<int> par;
int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
vector<int> JobScheduling(Job arr[], int n)
{
    // find the max days available
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        maxDeadline = max(maxDeadline, arr[i].dead);

    // parent array represents the days
    // each parent means the last day available <= current day
    par.resize(maxDeadline + 1);

    for (int i = 0; i <= maxDeadline; i++)
    {
        par[i] = i;
    }

    // sort in desc order of profit
    sort(arr, arr + n, [](Job j1, Job j2)
         { return j1.profit > j2.profit; });

    int totalProfit = 0, jobCount = 0;

    for (int i = 0; i < n; i++)
    {
        int jobid = arr[i].id;
        int deadline = arr[i].dead;
        int profit = arr[i].profit;

        // find the last available day from current deadline
        int p1 = find(deadline);

        // if last available day is not 0, then include this job
        if (p1 != 0)
        {
            jobCount++;
            totalProfit += profit;

            // merge it with its previous day's parent
            int p2 = find(p1 - 1);
            par[p1] = p2;
        }
    }

    return {jobCount, totalProfit};
}

// 839. Similar String Groups
/*
Approach: DSU
For all pairs of strings, check if they are similar
If they only differ at <=2 different positions from each other then they are similar
If they are similar, then merge them

For the parent array, and merge use indexes instead of string, 
because their are duplicate strings present in the given array

Eg:
[abc, abc, abc, abc]
If you make a hashmap of {string, string}, then it will never find different parents
so it will never merge.
So, use indexes for parent array.
*/
vector<int> par;
vector<int> rank;
int setCount;
int find(int &u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}
void merge(int u, int v)
{
    int p1 = find(u);
    int p2 = find(v);

    if (p1 != p2)
    {
        if (rank[p1] < rank[p2])
            par[p1] = p2;
        else if (rank[p2] < rank[p1])
            par[p2] = p1;
        else
        {
            par[p2] = p1;
            rank[p1]++;
        }

        setCount--;
    }
}
bool isSimilar(string &s1, string &s2)
{
    int count = 0;
    for (int k = 0; k < s1.size(); k++)
    {
        if (s1[k] != s2[k])
            count++;
        if (count > 2)
            return false;
    }

    return true;
}
int numSimilarGroups(vector<string> &strs)
{
    int n = strs.size();

    par.resize(n);
    rank.resize(n, 1);
    for (int i = 0; i < n; i++)
    {
        par[i] = i;
    }

    setCount = n;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (isSimilar(strs[i], strs[j]))
                merge(i, j);
        }
    }

    return setCount;
}

// Euler Path and Circuit
// Possible Path (https://practice.geeksforgeeks.org/problems/castle-run3644/1)
/*
Approach : Euler Circuit
It is an undirected graph. So, find the degree of all nodes. 
If the degree is even for all then it is a euler circuit and answer is true.
*/
int isPossible(vector<vector<int>> paths)
{
    int n = paths.size();

    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (paths[i][j] == 1)
            {
                degree[i]++;
                degree[j]++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (degree[i] % 2 != 0)
            return 0;
    }

    return 1;
}

// Minimum Swaps to Sort (https://practice.geeksforgeeks.org/problems/minimum-swaps/1)
/*
Approach : Cycle Detection
1. Sort the array and find the sorted indexes of each element
2. Now if elements have been swapped, then if we start putting each element back in its place
then cycles will be formed.

Eg: 
Array:  7 16 14 17 6 9 5 3 18
Sorted: 3 5 6 7 9 14 16 17 18
Index:  0 1 2 3 4 5 6 7  8 9

So for i = 0, i.e. 7
Its correct position is index = 3
So we go to i = 3.
Now at 3 is 17 which should be at 8
So go to 8.
Now at 8 is 3 which should be at 0
Go to 0. So, a cycle has been formed

0 -> 3 -> 8 -> 0
So minimum swaps for each cycle is size - 1 = 4 - 1 = 3

This way find all cycles and add the count to total swaps.
Also keep a visited so, you dont traverse the same cycle again.
*/
int minSwaps(vector<int> &nums)
{
    // Code here
    int n = nums.size();

    // sort the given array, and store the sorted indexes of each element in a map
    vector<int> temp = nums;

    sort(temp.begin(), temp.end());

    unordered_map<int, int> mp;
    vector<bool> vis(n);

    for (int i = 0; i < n; i++)
        mp[temp[i]] = i;

    int swapCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (vis[i])
            continue;

        vis[i] = true;
        int correctPos = mp[nums[i]];

        // until you complete the cycle and come back to the same index
        // keep going to the correct index of the current element
        int count = 0;
        while (correctPos != i)
        {
            vis[correctPos] = true;

            int num = nums[correctPos];
            correctPos = mp[num];

            count++;
        }

        swapCount += count;
    }

    return swapCount;
}

// https://codeforces.com/contest/1534/problem/C
/*
Approach: Cycle Detection
Similar to minimum swaps to sort, here also we have to detect cycles

Say we are at index i
Element in row1 = ele1
Element in row2 = ele2
Swap the elements at current index i.e ele2 comes to row1, ele1 goes to row2
This will cause duplicates in both rows since the elements we swapped would already be present there. 
So, for row 1 find the index of the other copy of the ele2 in row1
Then swap column at that index and repeat until the you find a copy of ele1 in row2 and swap it back to row1.

So, each cycle is gives us 1 configuration
So count number of such cycles.
Then your answer = 2 ^ cycleCount

Because we can combine different cycles to generate different configurations.
We basically have n cycles [c1, c2, c3, c4....cn]
So, we can take any subset of these and it will give a different configuration
And number of subsets = 2^n

For eg: 
Row 1:   2 6 5 1 4 3 7 8
Row 2:   3 8 7 5 1 2 4 6
Indexes: 0 1 2 3 4 5 6 7

First cycle will be at i = 0,
swap(2, 3) at i = 0
Then swap(3, 2) at i = 5

Second cycle at i = 1
swap(6, 8) at i=1
Then, swap(8, 6) at i = 7

Third Cycle at i = 2
swap(5, 7)  at i = 2
swap(7, 4) at i = 6
swap(4, 1) at i = 4
swap(1, 5) at i = 3

These are the 3 cycles present
Now, we form 2^3 = 8 different configurations using 3 cycles
*/
const long MOD = 1e9 + 7;
long long modPow(long long a, long long b)
{
    if (a == 0)
        return 0;
    if (b == 0)
        return 1;

    long long smallAns = (modPow(a, b / 2));

    smallAns = ((smallAns % MOD) * (smallAns % MOD)) % MOD;

    return b % 2 == 0 ? smallAns : ((smallAns % MOD * a % MOD) % MOD);
}
long long countCycles(vector<vector<int>> &arr)
{
    int n = arr[0].size();

    vector<bool> vis(n);
    unordered_map<int, int> mp1;

    for (int i = 0; i < n; i++)
        mp1[arr[0][i]] = i;

    long long count = 0;
    for (int i = 0; i < n; i++)
    {
        if (vis[i])
            continue;

        count++;

        vis[i] = true;
        int ele1 = arr[0][i];
        int ele2 = arr[1][i];

        int j = mp1[ele2];

        while (arr[1][j] != ele1)
        {
            vis[j] = true;
            ele2 = arr[1][j];
            j = mp1[ele2];

            swap(arr[0][j], arr[1][j]);
        }

        vis[j] = true;
        swap(arr[0][j], arr[1][j]);
    }

    return count;
}

void littleAlawanPuzzle()
{
    int t;
    cin >> t;

    while (t-- > 0)
    {
        int n;
        cin >> n;

        vector<vector<int>> arr(2, vector<int>(n));
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < n; j++)
                cin >> arr[i][j];

        long cycleCount = countCycles(arr);
        long res = modPow(2, cycleCount);

        cout << res << endl;
    }
}

// 773. Sliding Puzzle
/*
Approach: BFS
Push the initial board into queue.
Now pop the front of queue.
For the this board, we swap the 0 with all its adjacent elements
If the new board has not occured before then push it into que.
Then we continue like this until we get the solved board.

Answer will be the level count when we get the solved board

Since array size is 2x3 always, so we can hardcode the direction array, and solved puzzle configuration.
*/
int slidingPuzzle(vector<vector<int>> &board)
{
    int n = board.size();
    int m = board[0].size();

    // convert board to serialized string
    string puzzle = "";
    string solvedPuzzle = "123450";
    int pos;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            puzzle += (board[i][j] + '0');
            if (board[i][j] == 0)
                pos = i * m + j;
        }
    }

    // put the serialized directions for each in a 2D board in an array
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<vector<int>> graph{{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};

    // Use BFS to get the minimum moves required
    queue<pair<string, int>> que; //{puzzle, index of empty slot in puzzle}
    unordered_map<string, bool> vis;

    que.push({puzzle, pos});

    int moves = 0;

    while (que.size() > 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            pair<string, int> rnode = que.front();
            que.pop();

            string currPuzzle = rnode.first;
            int pos = rnode.second;

            if (currPuzzle == solvedPuzzle)
                return moves;

            // swap with 4 directions and push into queue
            for (int dirIdx : graph[pos])
            {
                string newPuzzle = currPuzzle;
                swap(newPuzzle[pos], newPuzzle[dirIdx]);

                if (!vis[newPuzzle])
                {
                    vis[newPuzzle] = true;
                    que.push({newPuzzle, dirIdx});
                }
            }
        }

        moves++;
    }

    return -1;
}

// 854. K-Similar Strings
/*
Approach: BFS
*/
int kSimilarity(string s1, string s2)
{
    queue<pair<string, int>> que;
    unordered_map<string, bool> vis;

    que.push({s2, 0});
    vis[s2] = true;

    int k = 0;

    while (que.size() > 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            pair<string, int> rnode = que.front();
            que.pop();

            string s = rnode.first;
            int idx = rnode.second;

            if (s == s1)
                return k;

            while (idx < s.size() && s[idx] == s1[idx])
                idx++;

            // check if we can swap the 2 elements such that both reach correct positions
            bool flag = false;
            for (int i = idx + 1; i < s.size(); i++)
            {
                if (s[i] == s1[i])
                    continue;

                if (s[i] == s1[idx] && s[idx] == s1[i])
                {
                    string temp = s;
                    swap(temp[i], temp[idx]);
                    if (!vis[temp])
                    {
                        que.push({temp, idx + 1});
                        flag = true;
                        break;
                    }
                }
            }

            if (flag)
                continue;

            // if we cant swap 2 elements into correct positions, then just find and swap the correct element at current index
            for (int i = idx + 1; i < s.size(); i++)
            {
                if (s[i] == s1[i])
                    continue;

                if (s[i] == s1[idx])
                {
                    string temp = s;
                    swap(temp[i], temp[idx]);
                    if (!vis[temp])
                        que.push({temp, idx + 1});
                }
            }
        }

        k++;
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}