#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <limits.h>
#include <algorithm>
// #define pair pair<int, int>

using namespace std;

// 463. Island Perimeter
/*
Approach:
Iterate over the grid
For each 1 add 4 to the answer
Then reduce 1 from answer for each of its neighbor that is 1
*/
int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    int res = 0;
    int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                // add 4 for this block
                res += 4;

                // subtract 1 for each neighbor
                for (int d = 0; d < 4; d++)
                {
                    int x = i + dir[d][0];
                    int y = j + dir[d][1];

                    if (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 1)
                        res -= 1;
                }
            }
        }
    }

    return res;
}

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

Here you will get two distinct islands: R$D$$ and RD$$
Without adding $ you will get RD for both

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
    unordered_set<string> islands;

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
For all 1s on the edges mark their islands as 0.
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
            // if already visited
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
/*
Approach: O(ElogV)
We mark visited when we pop from PQ, and not when adding to PQ
because we might find another edge to insert that vertex with smaller weight
So, only mark visited when it is removed from PQ, because then from PQ we get the 
min edge only.
*/
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
/*
Approach: MST
We can connect every point to every point
So, it is complete graph, and so we use Prims to find MST
And for each vertex, every point is its neighbor and distance is weight, 
so add them all to PQ.
*/
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
/*
Approach: MST
We basically have to form an MST with lowest max weight
So, we use Prims Algo, and instead of finding total weight of graph
we need the max weight.
Because it does not matter what the length of path from start to end is.
We only need to find path with min cost.
So, starting from {0,0} add its 4 unvisited neighbors into PQ
PQ contains {max weight till now, i, j}
Also, here we mark visited while adding to PQ
as the weight to the vertex is grid[i][j]
So, the weight remains same for all its edges.
*/
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
Bellman Ford algo (Single Source Shortest Path)
Time Complexity: O(E*V)
-ve, +ve edges allowed

If -ve cycle is present, then it will find it and return false

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
/*
Approach: O(V + E)
*/
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

    // 1. perform DFS make the stack
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs(graph, i, vis);
    }

    // 2. make the reverse graph
    vector<vector<int>> revGraph(n);
    vector<bool> nVis(n);
    for (int i = 0; i < n; i++)
    {
        for (int v : adj[i])
        {
            revGraph[v].push_back(i);
        }
    }

    // perform DFS using stack
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
2. Now the top element of stack can be the mother vertex or there is no mother vertex
3. Verify if top element is mother vertex

There can be more than 1 mother vertex, but the top of stack will definately be 
one of them, if it is not a mother vertex, then there are no mother vertex

This is because element is added to stack after it has done the DFS for all its children.
So, top of stack must have finished at the end because its neighbors were connected to 
max number of nodes and so they processed all nodes in the graph before they were all processed.
So, the vertex which can reach all other vertices will definetely finish last as it will
first process all nodes in the graph before all its work is done.
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

    // if count == number of vertices, then all were visited, so it is the mother vertex
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

        if (x >= 0 && y >= 0 && x < n && y < m)
        {
            if (grid[x][y] == 2)
                count++;

            if (grid[x][y] == 1)
            {
                dfs(grid, x, y);
                count++;
            }
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
/*
Approach: Kahn Algo, O(V+E)
Kahn Algo can also be used to detect cycle
If the size of result array is not equal to number of vertices,
then cycle is present
*/
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

    // build the graph
    for (int i = 0; i < n - 1; i++)
    {
        string word1 = words[i];
        string word2 = words[i + 1];

        int len = min(word1.size(), word2.size());
        int idx = 0;
        while (idx < len)
        {
            char u = word1[idx];
            char v = word2[idx];
            if (u != v)
            {
                graph[u].insert(v);
                break;
            }

            idx++;
        }

        // if the current word is before next word, but nothing in it is smaller then next word
        // and its length is also not less, then dictionary is invalid
        if (idx == len && word1.size() > word2.size())
            return "";
    }

    // find indegree
    unordered_map<char, int> indegree;

    // initialize indegree for all nodes
    for (int i = 0; i < n; i++)
    {
        for (char ch : words[i])
            indegree[ch] = 0;
    }

    for (auto e : graph)
    {
        for (auto v : e.second)
            indegree[v]++;
    }

    //Kahn's Algo to find answer

    // Lintcode wants the lexicographically smaller answer from possible answers
    // So, PQ is used, otherwise normal queue can be used

    priority_queue<char, vector<char>, greater<char>> que;
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
            indegree[v]--;
            if (indegree[v] == 0)
                que.push(v);
        }
    }

    // if the res does not include all nodes, then there is a cycle
    // so return ""
    return res.size() == indegree.size() ? res : "";
}

// Disjoint Set Union (DSU)
/*
find() takes O(n) in worst case without the union/merge
merge() will take O(1)
Using merge, find takes O(logn)
*/
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
            break;
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
Approach: Articulation Points, O(V+E) as it is a DFS
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

    if (par[src] == 0) // current node's parent is the root
    {
        srcCount++;
        // if root has been reached more than 1 time, then it is also an Articulation point
        if (srcCount >= 2)
            ap[src] = true;
    }

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

            // check if current node is an Articulation Point
            if (low[v] >= disc[src])
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

        cout << res - 1 << endl;
    }
}

// 1192. Critical Connections in a Network
/*
Approach: Articulation Bridges
Same as Articulation Points
We just dont need to check seperately for root, and the condition

// check if current node is an Articulation Point
if (low[v] >= disc[src])
    ap[src] = true;

Changes to:

// check if this edge is Articulation Bridge
if (low[v] > disc[src])
    res.push_back({src, v});

Because we are removing the edge so just check if lowest the neighbor can visit is after
the current edge

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
Approach 1: Greedy, O(n^2)
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

            // find the index of first element not in its correct position
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

// Find the Maximum Flow (Ford Fulkerson and Edmond's Karp Algo)
int solve(int N, int M, vector<vector<int>> Edges)
{
    // code here
}

// Euler Path and Circuit
// Eulerian Path in an Undirected Graph
/*
Approach:
For a Euler Path in undirected Graph:
1. Either allx nodes have even degrees (Euler Circuit)
OR
2. N-2 Nodes have even Degrees, 2 nodes have odd degrees
*/
int eulerPath(int N, vector<vector<int>> graph)
{
    int n = N;

    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (graph[i][j] == 1)
            {
                degree[i]++;
                degree[j]++;
            }
        }
    }

    int oddCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (degree[i] % 2 != 0)
            oddCount++;

        if (oddCount > 2)
            return 0;
    }

    return 1;
}
// Possible Path (https://practice.geeksforgeeks.org/problems/castle-run3644/1) (Not Correctly Submitted)
/*
Approach : Check if Euler Circuit is present
It is an undirected graph. So, find the degree of all nodes. 
If the degree is even for all then it is a euler circuit and answer is true.
*/
int isPossible(vector<vector<int>> paths)
{
    int n = paths.size();

    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (paths[i][j] == 1)
            {
                // degree[i]++;
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

// 332. Reconstruct Itinerary (Euler Path)
/*
Approach: Find the Euler Path
To find eulerian path, start from source, and do a normal DFS
And in backtracking add current node to answer.
This is the path in reverse so reverse it at the end
Also to get the lexicographical order, build the adjacency as a map
{node : min PQ of neighbors}
*/
// Using Min PQ to maintain the lexicographical order
vector<string> path;
unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
void eulerianPath(string &src)
{
    while (graph[src].size() > 0)
    {
        string rnode = graph[src].top();
        graph[src].pop();

        eulerianPath(rnode);
    }

    path.push_back(src);
}
vector<string> findItinerary(vector<vector<string>> &tickets)
{
    for (vector<string> &e : tickets)
    {
        graph[e[0]].push(e[1]);
    }

    string src = "JFK";
    eulerianPath(src);

    reverse(path.begin(), path.end());

    return path;
}

// Faster: Using a Multiset to maintain lexicographical order
vector<string> path;
unordered_map<string, multiset<string>> graph;
void eulerianPath(string &src)
{
    while (graph[src].size() > 0)
    {
        string rnode = *graph[src].begin();
        graph[src].erase(graph[src].begin());

        eulerianPath(rnode);
    }

    path.push_back(src);
}
vector<string> findItinerary(vector<vector<string>> &tickets)
{
    for (vector<string> &e : tickets)
    {
        graph[e[0]].insert(e[1]);
    }

    string src = "JFK";
    eulerianPath(src);

    reverse(path.begin(), path.end());

    return path;
}

// Floyd Warshall (GFG)
/*
Approach:
Time: O(V^3)
*/
void shortest_distance(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (k == i || k == j)
                    continue;

                // if there is no edge b/w i,j and there is an edge b/w i,k and k,j
                // then update i,j
                if (matrix[i][j] == -1 && matrix[i][k] != -1 && matrix[k][j] != -1)
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                // else if the cost b/w i,j > cost(i,k) + cost(k,j), then update i,j
                else if (matrix[i][k] != -1 && matrix[k][j] != -1)
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}

// 1579. Remove Max Number of Edges to Keep Graph Fully Traversable
/*
Approach: DSU
We use DSU to build 2 graphs, one for alice, and one for bob
So, for each edge we add it to one of the graphs or both graphs depending on its color

From the 3 edge types 3 is most favorable, as it can be added to both graphs
Then edge 1 is added to alice's graph, 2 is added to bob's graph

Using DSU, if the two vertices are already connected, then this edge can be removed
And at the end the set count for both graphs should be 1, i.e. there should be one
component in both alice's and bob's graph
*/
vector<int> par1;
vector<int> par2;
int count1, count2;
int find(int u, vector<int> &par)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u], par);
}
bool merge1(int u, int v)
{
    int p1 = find(u, par1);
    int p2 = find(v, par1);

    if (p1 == p2)
        return true;

    par1[p1] = p2;
    count1--;

    return false;
}
bool merge2(int u, int v)
{
    int p1 = find(u, par2);
    int p2 = find(v, par2);

    if (p1 == p2)
        return true;

    par2[p1] = p2;
    count2--;

    return false;
}
int maxNumEdgesToRemove(int n, vector<vector<int>> &edges)
{
    int totalEdges = edges.size();

    // sort to bring edge 3 first, so that they are processed first
    sort(edges.begin(), edges.end(), greater<vector<int>>());

    for (int i = 0; i <= n; i++)
    {
        par1.push_back(i);
        par2.push_back(i);
    }

    count1 = n;
    count2 = n;

    int removedEdges = 0;

    for (vector<int> &e : edges)
    {
        int u = e[1];
        int v = e[2];
        int color = e[0];

        if (color == 3)
        {
            bool flag1 = merge1(u, v);
            bool flag2 = merge2(u, v);
            if (flag1 && flag2)
                removedEdges++;
        }
        else if (color == 1)
        {
            if (merge1(u, v))
                removedEdges++;
        }
        else if (color == 2)
        {
            if (merge2(u, v))
                removedEdges++;
        }
    }

    return (count1 == 1 && count2 == 1) ? removedEdges : -1;
}

// 787. Cheapest Flights Within K Stops
/*
Approach 1: Dijkstra Algo
Use a Min PQ (price, node stops)
We cant use a visited array directly because we may visit the same node with less stops again.
EG:
5
[[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1]]
0
2
2

Here we reach the node 1 with less price first but we have already used k stops.
So, we can reach it again in less stops by a different path. 
So, instead of a visited, we keep a cost and a stops array.
and before pushing into PQ, we check if we are reaching that node with either less cost or less stops
Then only we push it into PQ.

Without this check the complexity is bad. It gives TLE.

Approach 2: Bellman Ford
In Bellman ford, at a time for the k'th iteration we will have the answers for atleast kth distance nodes in the array.
But we need strictly kth. So, we keep 2 arrays prev, curr.
We use prev array to update the values, and update them in the curr array.
Then for the next iteration we make the curr array as prev, and a new curr array.
For k stops we do this k+1 times because the destination will be at the (k+1)th node.
*/
// Approach 1: Dijkstra Algo
int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
{
    typedef pair<int, int> pair;
    vector<vector<pair>> graph(n);

    for (int i = 0; i < flights.size(); i++)
    {
        int u = flights[i][0];
        int v = flights[i][1];
        int w = flights[i][2];

        graph[u].push_back({v, w});
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> cost(n, INT_MAX);
    vector<int> stops(n, n);

    pq.push({0, src, 0}); //{ price, node, number of stops}

    while (pq.size() > 0)
    {
        vector<int> rnode = pq.top();
        pq.pop();

        int price = rnode[0];
        int currStop = rnode[1];
        int stopCount = rnode[2];

        if (currStop == dst)
        {
            return price;
        }
        else if (stopCount > k)
            continue;

        for (pair &e : graph[currStop])
        {
            if (cost[e.first] > e.second + price || stops[e.first] > stopCount + 1)
            {
                cost[e.first] = e.second + price;
                stops[e.first] = stopCount + 1;
                pq.push({price + e.second, e.first, stopCount + 1});
            }
        }
    }

    return -1;
}
// Approach 2: Bellman Ford
int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
{
    vector<int> prev(n, INT_MAX);
    prev[src] = 0;
    vector<int> curr;

    for (int i = 0; i <= k; i++)
    {
        curr.assign(n, INT_MAX);
        curr[src] = 0;

        // get the minimum distance to all stops at ith distance
        for (vector<int> &e : flights)
        {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            if (prev[u] == INT_MAX)
                continue;

            if (prev[u] + w < curr[v])
                curr[v] = prev[u] + w;
        }

        prev = curr;
    }

    return curr[dst] == INT_MAX ? -1 : curr[dst];
}

// 803. Bricks Falling When Hit
/*
Approach: DSU
Remove all the bricks given in the query
To do this mark the bricks that are 1, as 2 and leave 0 as 0

Then use Union Find. Use a 1D parent array of size n*m + 1
For each cell, convert it to 1D index. The nodes are 1 based.
We use 0th index as default parent of all 0th row 1s
So add all 1s in 0th row to same set with 0 as parent.
Then make sets for all remaining 1s

Now iterate through queries in reverse
If that brick is 0, then skip it, if it is 2, then it was 1 before
So, merge it to a set with its adjacent elements.
Then if this brick was in 0th row, then add it to the set of 0 as well

Then find the difference in size of set 0 before and after adding that brick
That diff - 1(for this brick), is the number of bricks that would fall if this brick is removed.
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
        //  if one of u, v is 0, make 0 the parent always
        if (p1 == 0 || p2 == 0)
        {
            if (p1 == 0)
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
        // else merge on basis of size
        else if (size[p1] < size[p2])
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
}
vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits)
{
    int n = grid.size();
    int m = grid[0].size();

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<int> res(hits.size());

    for (int i = 0; i <= n * m; i++)
    {
        par.push_back(i);
        size.push_back(1);
    }

    // remove the bricks given in queries from the grid
    for (vector<int> &v : hits)
    {
        if (grid[v[0]][v[1]] == 1)
            grid[v[0]][v[1]] = 2;
    }

    // make the sets of 1s in the 1st row, making 0 as parent
    for (int j = 0; j < m; j++)
    {
        if (grid[0][j] == 1)
        {
            int v = j + 1;
            merge(0, v);
        }
    }

    // make the sets of remaining 1s
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                int u = i * m + j + 1;
                for (int d = 0; d < 4; d++)
                {
                    int x = i + dir[d][0];
                    int y = j + dir[d][1];

                    if (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 1)
                    {
                        int v = x * m + y + 1;
                        merge(u, v);
                    }
                }
            }
        }
    }

    // solve queries in reverse order
    for (int k = hits.size() - 1; k >= 0; k--)
    {
        int i = hits[k][0];
        int j = hits[k][1];

        if (grid[i][j] == 2)
            grid[i][j] = 1;
        else
            continue;

        int sizeBeforeMerge = size[0];

        // merge this brick with all its adjacent bricks
        int u = i * m + j + 1;
        for (int d = 0; d < 4; d++)
        {
            int x = i + dir[d][0];
            int y = j + dir[d][1];

            if (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 1)
            {
                int v = x * m + y + 1;
                merge(u, v);
            }
        }

        //merge its set with 0s set if it is in first 0th row
        if (i == 0)
            merge(0, u);

        int sizeAfterMerge = size[0];

        int diff = abs(sizeAfterMerge - sizeBeforeMerge) - 1;
        if (diff > 0)
            res[k] = diff;
    }

    return res;
}

// 1202. Smallest String With Swaps
/*
Approach: Union Find
https://leetcode.com/problems/smallest-string-with-swaps/discuss/388257/C%2B%2B-with-picture-union-find

As given in this discuss, iterate over all pairs, and group them into sets
Then sort each set individually
Then put those characters back into the string at their respective postions
Eg:
"zdcyxbwa"
[[0,3],[4,6],[3,4],[1,7],[2,5],[5,7]]

We get the sets:
1. zyxw -> after sorting it is wxyz
2. dcba -> after sorting it is abcd

Now put them back in their correct positons
Like w goes in position of z
x goes in position of y and so on...

*/
vector<int> par;
unordered_map<int, priority_queue<char, vector<char>, greater<char>>> mp; // {parent: Min PQ of chars in that set}
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
        if (mp[p1].size() > mp[p2].size())
        {
            par[p2] = p1;
            while (mp[p2].size() > 0)
            {
                char ch = mp[p2].top();
                mp[p2].pop();

                mp[p1].push(ch);
            }
        }
        else
        {
            par[p1] = p2;
            while (mp[p1].size() > 0)
            {
                char ch = mp[p1].top();
                mp[p1].pop();

                mp[p2].push(ch);
            }
        }
    }
}
string smallestStringWithSwaps(string s, vector<vector<int>> &pairs)
{
    string res = "";

    // initialize the parent array, and the map
    for (int i = 0; i < s.size(); i++)
    {
        par.push_back(i);
        mp[i].push(s[i]);
    }

    // make the sets of all pairs
    for (int i = 0; i < pairs.size(); i++)
    {
        int u = pairs[i][0];
        int v = pairs[i][1];

        merge(u, v);
    }

    // for each element in string s,
    for (int i = 0; i < s.size(); i++)
    {
        // get the top of PQ of its parent i.e. the smallest element in its set
        // and add it to the answer
        int p = find(i);
        res += mp[p].top();

        mp[p].pop();
    }

    return res;
}

// 1203. Sort Items by Groups Respecting Dependencies (Not Complete)
/*
Approach: Topological Sort
1. Make the graph using group and beforeItems array

For node a with beforeItem b
If the before node and this node are in same group, then add edge before node to this node
else Get the end node of node b and add a directed edge from b to end node and end node to a

And for its group g, get the group's start and end node
start node : no. of nodes + 2 * group no.
end node: no. of nodes + 2 * group no. + 1

If the before node and this node are in same group, then add edge before node to this node

2. Apply Topological sort
To apply topological sort we we iterate over the indgrees and for each indegree==0
we call topological sort with that node as source.

Eg:
Item    Group   Before
0       -1
1       -1        6
2        1        5
3        0        6
4        0       3,6
5        1
6        0
7       -1

Graph:
0 -> 
1 -> 
2 -> 11 
3 -> 4 9 
4 -> 9 
5 -> 11 2 
6 -> 9 4 3 
7 -> 
8 -> 6 4 3 
9 -> 1 
10 -> 5 2 
11 -> 

Indexes:  0 1 2 3 4 5 6 7 8 9 10 11
Indegree: 0 1 2 2 3 1 1 0 0 3 0  2
*/
vector<int> res;
vector<int> indegree;
queue<int> que;
vector<bool> vis;
void topologicalSort(vector<unordered_set<int>> &graph, int n, int src)
{
    queue<int> que;

    que.push(src);

    while (que.size() > 0)
    {
        int rnode = que.front();
        que.pop();

        indegree[rnode]--;
        if (rnode < n)
        {
            res.push_back(rnode);
        }

        for (int v : graph[rnode])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                que.push(v);
            }
        }
    }
}
vector<int> sortItems(int n, int m, vector<int> &group, vector<vector<int>> &beforeItems)
{
    int totalNodes = n + 2 * m;
    vector<unordered_set<int>> graph(totalNodes);
    indegree.resize(totalNodes);
    vis.resize(totalNodes);

    // graph construction
    for (int i = 0; i < n; i++)
    {
        int currHead = (group[i] == -1) ? i : (n + 2 * group[i]);
        int currTail = (group[i] == -1) ? i : (n + 2 * group[i] + 1);

        if (group[i] != -1)
        {
            graph[currHead].insert(i);
            graph[i].insert(currTail);
        }

        for (int u : beforeItems[i])
        {
            int beforeItemTail = (group[u] == -1) || (group[u] == group[i]) ? u : (n + 2 * group[u] + 1);
            int currHead = (group[i] == -1) || (group[u] == group[i]) ? i : (n + 2 * group[i]);

            graph[beforeItemTail].insert(currHead);
        }
    }
    for (int i = 0; i < graph.size(); i++)
    {
        for (int v : graph[i])
        {
            indegree[v]++;
        }
    }

    // Topological Sort
    for (int i = 0; i < totalNodes; i++)
    {
        if (indegree[i] == 0)
        {
            topologicalSort(graph, n, i);
        }
    }

    return res.size() == n ? res : vector<int>();
}

// 802. Find Eventual Safe States
/*
Approach: Cycle Detection in Directed Graph
The safe nodes are those nodes that are not part of any cycle.
So, we detect all cycles in graph.

We a visited to store, if current node is:
1. Unvisited
2. Visited
    a. Safe
    b. Unsafe

We keep a visited array in which we mark:
0: unvisited
1: visited and safe
2: visited and unsafe

For the current node, we initialise it as unsafe
Then we call dfs for all its neighbors
If all neighbors are marked safe, then only we mark this node as safe
Also in base case, check if this node has been visited before:
1. It was marked unsafe, then return false
2. It was marked safe, then return true

If there is a cycle and this node is visited again by a neighbor, then it
would still have been marked unsafe, and so it will directly return unsafe

For each node if it is visited in the DFS again, then it is part of a cycle
Then it is unsafe.

At the end iterate over visited array and push all nodes marked 1, into result
as they are safe.
*/
bool isSafe(vector<vector<int>> &graph, int src, vector<int> &vis)
{
    // if already visited
    if (vis[src] == 1)  // was marked safe
        return true;
    if (vis[src] == 2)  // was marked unsafe
        return false;

    // else initialise current node as unsafe
    vis[src] = 2;

    for (int v : graph[src])
    {
        // if any neighbor is unsafe, then this is also unsafe
        if (!isSafe(graph, v, vis))
            return false;
    }

    // mark current node as safe
    vis[src] = 1;

    return true;
}
vector<int> eventualSafeNodes(vector<vector<int>> &graph)
{
    int n = graph.size();

    vector<int> vis(n); // 0: unvisited, 1: safe, 2: unsafe

    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            isSafe(graph, i, vis);
        }
    }

    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 1)
        {
            res.push_back(i);
        }
    }

    return res;
}

// 1627. Graph Connectivity With Threshold
/*
Approach: DSU
For each query we have to check if the two nodes are connected directly or indirectly
So, Connect each node greater than threshold with all its multiples
Use Union Find, to make sets of all these nodes.
Then for each query, just check if they belong to the same set

We cannot use gcd to check if they are connected because it only checks direct connections.
*/
vector<int> par;
vector<int> rank;
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
        if (rank[p1] < rank[p2])
        {
            par[p1] = p2;
        }
        else if (rank[p2] < rank[p1])
        {
            par[p2] = p1;
        }
        else
        {
            par[p2] = p1;
            rank[p1]++;
        }
    }
}
vector<bool> areConnected(int n, int threshold, vector<vector<int>> &queries)
{
    par.resize(n + 1);
    rank.resize(n + 1, 1);

    for (int i = 1; i <= n; i++)
        par[i] = i;

    // merge every number > threshold with all its multiples
    for (int u = threshold + 1; u <= n; u++)
    {
        int i = 2;
        while (u * i <= n)
        {
            merge(u, u * i);
            i++;
        }
    }

    vector<bool> res(queries.size());

    for (int i = 0; i < queries.size(); i++)
    {
        int a = queries[i][0];
        int b = queries[i][1];

        int p1 = find(a);
        int p2 = find(b);

        // if the 2 numbers belong to same set, then they are connected
        if (p1 == p2)
            res[i] = true;
    }

    return res;
}

// 743. Network Delay Time
/*
Approach: Dijkstra Algo
*/
int networkDelayTime(vector<vector<int>> &times, int n, int k)
{
    vector<vector<vector<int>>> graph(n + 1);

    for (vector<int> &e : times)
    {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        graph[u].push_back({v, w});
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> cost(n + 1, INT_MAX);
    cost[k] = 0;
    pq.push({0, k}); // {cost, node}

    while (pq.size() > 0)
    {
        vector<int> rnode = pq.top();
        pq.pop();

        for (vector<int> &e : graph[rnode[1]])
        {
            if (cost[e[0]] > rnode[0] + e[1])
            {
                pq.push({rnode[0] + e[1], e[0]});
                cost[e[0]] = rnode[0] + e[1];
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        // if any node is unvisited, then return -1
        if (cost[i] == INT_MAX)
            return -1;

        res = max(res, cost[i]);
    }

    return res;
}

// Web of Lies (https://codeforces.com/problemset/problem/1548/A)
/*
Approach: 
Preprocess: O(n)
Query: O(1)

Consider it as a directed graph with edges going from smaller to larger node
Every node with zero outdegree is safe as it has no neighbor greater than itself
So, from the given edges just count the outdegree of each node.
Then every node with zero outdegree is safe.

For Query 1, Add an edge
The question says that the edge will not be present before
So, if the outdegree of the min(u, v) for the new edge is 0, then it was safe
But it has a > neighbor now, so decrease safe nodes

For Query 2, Remove an edge
The question says that the edge will be present
So, if the outdegree of the min(u, v) for that edge is 1, then it was not safe
But its neighbor got removed so it is safe now

For Query 3, 
Just print the safe nodes count
*/
void webOfLies()
{
    int n, m;
    cin >> n >> m;

    vector<int> outdegree(n);
    int safeNodes = 0;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        // increase outdegree of smaller node
        outdegree[min(u, v)]++;
    }

    // count number of safe nodes
    for (int deg : outdegree)
        if (deg == 0)
            safeNodes++;

    int q;
    cin >> q;

    while (q--)
    {
        int query;
        cin >> query;

        // add edge
        if (query == 1)
        {
            int u, v;
            cin >> u >> v;

            if (outdegree[min(u, v)] == 0)
                safeNodes--;

            outdegree[min(u, v)]++;
        }
        // remove edge
        else if (query == 2)
        {
            int u, v;
            cin >> u >> v;

            if (outdegree[min(u, v)] == 1)
                safeNodes++;

            outdegree[min(u, v)]--;
        }
        // print safe node count
        else
        {
            cout << safeNodes << "\n";
        }
    }
}

// Extra==========================================================================

// 127. Word Ladder
/*
Eg:
beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]

Approach 1: BFS, Time: O(n^2 * m), Space: O(n^2) 
where, n = length of wordList, m = length of word
Preprocess and make an adjacency list
For every word, make an edge between that word and every other word which only
differs by 1 character.
So, we will use O(n^2) time to run the loop to find the similar words and 
O(m) to compare them
Like in above example, for we will have
hot: dot, lot
dot: hot, lot, dog
dog: dot, log, cog
and so on...

Then just run a BFS and find the shortest path between beginWord, endWord

Approach 2: BFS, Time: O(n * m^2), Space: O(n * m^2)
Instead of running the O(n^2) loop, we can do the following
hot can have the transformations: *ot, h*t, ho*
So, make hashmap of {transformation: list of words with that transformation}
Eg: In above example, we will have a hashmap:
*ot: hot, dot, lot
h*t: hot
ho*: hot
do*: dot, dog
d*t: dot
and so on ...

And then use this to run the BFS

In these 2 approaches, we avoid the preprocessing if we put whole wordList in a hashset
Then for each pattern instead of putting *, just put every letter one by one 
and search for that word in the set directly
This will make the complexity Time: O(n * m^2 * 26)

Approach 3: Bidirectional BFS, Time: O(n * m^2), Space: O(n * m^2)
We start a BFS from both the beginWord, and endWord.
Then it will meet in the middle and the time complexity will become half of the 
normal BFS in first 2 approaches.

*/
// Approach 1
bool isSimilar(string &word1, string &word2)
{
    if (word1.size() != word2.size())
        return false;

    bool flag = false;
    for (int i = 0; i < word1.size(); i++)
    {
        if (word1[i] != word2[i])
        {
            if (!flag)
                flag = true;
            else
                return false;
        }
    }

    return true;
}
int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    unordered_map<int, vector<int>> similarWords;
    queue<int> que;
    vector<bool> vis(wordList.size());
    int count = 1;

    for (int i = 0; i < wordList.size(); i++)
    {
        // add all words similar to current word to the hashmap
        for (int j = i + 1; j < wordList.size(); j++)
        {
            if (isSimilar(wordList[i], wordList[j]))
            {
                similarWords[i].push_back(j);
                similarWords[j].push_back(i);
            }
        }

        // if this is the beginWord, then mark it as true
        if (wordList[i] == beginWord)
            vis[i] = true;
        // if this word is similar to beginWord, then push it into the queue for BFS
        else if (isSimilar(beginWord, wordList[i]))
        {
            que.push(i);
            vis[i] = true;

            if (wordList[i] == endWord)
                return count + 1;
        }
    }

    while (que.size() > 0)
    {
        int size = que.size();
        count++;

        while (size--)
        {
            int rIdx = que.front();
            que.pop();

            // push all similar words for the current word into the queue
            for (int idx : similarWords[rIdx])
            {
                if (wordList[idx] == endWord)
                    return count + 1;

                if (!vis[idx])
                {
                    que.push(idx);
                    vis[idx] = true;
                }
            }
        }
    }

    return 0;
}
// Approach 2
int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    unordered_map<string, vector<int>> patterns;
    vector<bool> vis(wordList.size());

    // make the pattern hashmap
    for (int i = 0; i < wordList.size(); i++)
    {
        string &word = wordList[i];
        // add the current word to every pattern that it can be made
        for (int j = 0; j < wordList[i].size(); j++)
        {
            char ch = word[j];
            word[j] = '*';
            patterns[word].push_back(i);
            word[j] = ch;
        }
    }

    queue<int> que;
    int count = 1;

    // for all the patterns of beginWord, add all those words into the queue for BFS
    for (int i = 0; i < beginWord.size(); i++)
    {
        char ch = beginWord[i];
        beginWord[i] = '*';

        for (int idx : patterns[beginWord])
        {
            if (wordList[idx] == endWord)
                return count + 1;

            que.push(idx);
            vis[idx] = true;
        }

        patterns.erase(beginWord);
        beginWord[i] = ch;
    }

    while (que.size() > 0)
    {
        int size = que.size();
        count++;

        while (size--)
        {
            string word = wordList[que.front()];
            que.pop();

            // for the current word, make its patterns and add those words into the queue
            for (int i = 0; i < word.size(); i++)
            {
                char ch = word[i];
                word[i] = '*';

                for (int idx : patterns[word])
                {
                    if (vis[idx])
                        continue;

                    if (wordList[idx] == endWord)
                        return count + 1;

                    que.push(idx);
                    vis[idx] = true;
                }

                patterns.erase(word);
                word[i] = ch;
            }
        }
    }

    return 0;
}
// Approach 2: Without preprocessing
int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    unordered_set<string> words(wordList.begin(), wordList.end());
    unordered_map<string, bool> vis;

    if (words.find(endWord) == words.end())
        return 0;

    queue<string> que;
    que.push(beginWord);
    int count = 0;

    while (que.size() > 0)
    {
        int size = que.size();
        count++;

        while (size--)
        {
            string word = que.front();
            que.pop();

            // for the current word, make its patterns and add those words into the queue
            for (int i = 0; i < word.size(); i++)
            {
                char ch = word[i];

                for (int j = 0; j < 26; j++)
                {
                    word[i] = (j + 'a');

                    if (word == endWord)
                        return count + 1;

                    if (vis[word])
                        continue;

                    if (words.find(word) != words.end())
                    {
                        que.push(word);
                        vis[word] = true;
                    }
                }

                word[i] = ch;
            }
        }
    }

    return 0;
}
// Approach 3:
int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    int n = wordList.size();

    unordered_map<string, vector<int>> patterns;
    bool flag = false;

    // make the pattern hashmap
    for (int i = 0; i < wordList.size(); i++)
    {
        string &word = wordList[i];
        // add the current word to every pattern that it can be made
        for (int j = 0; j < wordList[i].size(); j++)
        {
            char ch = word[j];
            word[j] = '*';
            patterns[word].push_back(i);
            word[j] = ch;
        }

        if (wordList[i] == endWord)
            flag = true;
    }

    if (!flag)
        return 0;

    queue<int> beginQue, endQue;
    vector<int> beginVis(n), endVis(n);
    int count = 1;

    // for all the patterns of beginWord, add all those words into the beginQueue for BFS
    for (int i = 0; i < beginWord.size(); i++)
    {
        char ch = beginWord[i];
        beginWord[i] = '*';

        for (int idx : patterns[beginWord])
        {
            if (wordList[idx] == endWord)
                return count + 1;

            beginQue.push(idx);
            beginVis[idx] = count + 1;
        }

        patterns.erase(beginWord);
        beginWord[i] = ch;
    }
    // for all the patterns of endWord, add all those words into the endQueue for BFS
    for (int i = 0; i < endWord.size(); i++)
    {
        char ch = endWord[i];
        endWord[i] = '*';

        for (int idx : patterns[endWord])
        {
            if (beginVis[idx] > 0)
                return beginVis[idx] + count;

            endQue.push(idx);
            endVis[idx] = count + 1;
        }

        patterns.erase(endWord);
        endWord[i] = ch;
    }
    // mark beginWord and endWord visited as well
    for (int i = 0; i < wordList.size(); i++)
    {
        if (wordList[i] == beginWord)
            beginVis[i] = 1;
        else if (wordList[i] == endWord)
            endVis[i] = 1;
    }

    while (beginQue.size() > 0 && endQue.size() > 0)
    {
        count++;

        int size = beginQue.size();
        while (size--)
        {
            string word = wordList[beginQue.front()];
            beginQue.pop();

            // for the current word, make its patterns and add those words into the queue
            for (int i = 0; i < word.size(); i++)
            {
                char ch = word[i];
                word[i] = '*';

                for (int idx : patterns[word])
                {
                    // already visited by endQue
                    if (endVis[idx] > 0)
                        return count + endVis[idx];

                    beginQue.push(idx);
                    beginVis[idx] = count + 1;
                }

                patterns.erase(word);
                word[i] = ch;
            }
        }

        size = endQue.size();
        while (size--)
        {
            string word = wordList[endQue.front()];
            endQue.pop();

            // for the current word, make its patterns and add those words into the queue
            for (int i = 0; i < word.size(); i++)
            {
                char ch = word[i];
                word[i] = '*';

                for (int idx : patterns[word])
                {
                    // already visited by beginQue
                    if (beginVis[idx] > 0)
                        return count + beginVis[idx];

                    endQue.push(idx);
                    endVis[idx] = count + 1;
                }

                patterns.erase(word);
                word[i] = ch;
            }
        }
    }

    return 0;
}

// 126. Word Ladder II
/*
Approach: BFS
Use the Approach 2 of Word Ladder
In the queue, push the entire vector of words till now
And in visited, mark it visited for the next level
Eg:
"red"
"tax"
["ted","tex","red","tax","tad","den","rex","pee"]

Ans: [["red","ted","tad","tax"],["red","ted","tex","tax"],["red","rex","tex","tax"]]
Here we will mark "tex" visited for the next level
We should still be able to use it for the current level.
So, in visited instead of bool put the level number
*/
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
{
    int n = wordList.size();

    unordered_map<string, vector<int>> patterns;
    vector<vector<string>> res;
    vector<int> vis(n, n + 1);

    // make the pattern hashmap
    for (int i = 0; i < wordList.size(); i++)
    {
        string &word = wordList[i];
        // add the current word to every pattern that it can be made
        for (int j = 0; j < wordList[i].size(); j++)
        {
            char ch = word[j];
            word[j] = '*';
            patterns[word].push_back(i);
            word[j] = ch;
        }
    }

    queue<vector<string>> que;
    que.push({beginWord});

    while (que.size() > 0)
    {
        int size = que.size();

        while (size--)
        {
            vector<string> list = que.front();
            string word = list[list.size() - 1];
            que.pop();

            for (int i = 0; i < word.size(); i++)
            {
                char ch = word[i];
                word[i] = '*';

                for (int idx : patterns[word])
                {
                    // if visited on previous levels then skip
                    if (vis[idx] < list.size())
                        continue;

                    list.push_back(wordList[idx]);

                    if (wordList[idx] == endWord)
                        res.push_back(list);
                    else
                    {
                        que.push(list);
                        vis[idx] = list.size() - 1;
                    }

                    list.pop_back();
                }

                word[i] = ch;
            }
        }

        if (res.size() > 0)
            return res;
    }

    return {};
}

// 1615. Maximal Network Rank
int maximalNetworkRank(int n, vector<vector<int>> &roads)
{
    vector<int> degree(n);
    vector<unordered_map<int, int>> graph(n);

    for (vector<int> &e : roads)
    {
        degree[e[0]]++;
        degree[e[1]]++;
        graph[e[0]][e[1]] = 1;
        graph[e[1]][e[0]] = 1;
    }

    int maxRank = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            maxRank = max(maxRank, degree[i] + degree[j] - graph[i][j]);
        }
    }

    return maxRank;
}

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}