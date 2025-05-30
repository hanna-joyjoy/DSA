#include <iostream>
#include <fstream>
#include <vector>
#include <queue>       
#include <stack>       
#include <numeric>     
#include <algorithm>   
#include <utility> 
#include <functional>
#include <climits> 

using namespace std;



vector<vector<int>> convertMatrixToList(const string& filename) 
{
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fin >> matrix[i][j];
    fin.close();

    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j])
                adjList[i].push_back(j);
    return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename) 
{
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        int count;
        fin >> count;
        for (int j = 0; j < count; ++j) 
        {
            int v;
            fin >> v;
            adjMatrix[i][v] = 1;
        }
    }
    fin.close();
    return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adjMatrix[i][j] != adjMatrix[j][i])
                return true;
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) 
{
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) 
{
    int edges = 0, n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            edges += adjMatrix[i][j];
    return isDirected(adjMatrix) ? edges : edges / 2;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) 
{
    vector<int> isolated;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) 
    {
        bool isolatedNode = true;
        for (int j = 0; j < n; ++j) 
        {
            if (adjMatrix[i][j] || adjMatrix[j][i]) 
            {
                isolatedNode = false;
                break;
            }
        }
        if (isolatedNode)
            isolated.push_back(i);
    }
    return isolated;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && adjMatrix[i][j] == 0)
                return false;
    return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    for (int start = 0; start < n; ++start) 
    {
        if (color[start] != -1) continue;
        color[start] = 0;
        q.push(start);
        while (!q.empty()) 
        {
            int u = q.front(); 
            q.pop();
            for (int v = 0; v < n; ++v) 
            {
                if (adjMatrix[u][v]) 
                {
                    if (color[v] == -1) 
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if (color[v] == color[u]) 
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) 
{
    if (!isBipartite(adjMatrix)) return false;
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    vector<int> set[2];

    for (int start = 0; start < n; ++start) 
    {
        if (color[start] != -1) continue;
        color[start] = 0;
        q.push(start);
        while (!q.empty()) 
        {
            int u = q.front(); 
            q.pop();
            set[color[u]].push_back(u);
            for (int v = 0; v < n; ++v) 
            {
                if (adjMatrix[u][v]) 
                {
                    if (color[v] == -1) 
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                }
            }
        }
    }

    for (int u : set[0])
        for (int v : set[1])
            if (!adjMatrix[u][v] || !adjMatrix[v][u])
                return false;
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<vector<int>> result = adjMatrix;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adjMatrix[i][j] || adjMatrix[j][i])
                result[i][j] = result[j][i] = 1;
    return result;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<vector<int>> comp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && adjMatrix[i][j] == 0)
                comp[i][j] = 1;
    return comp;
}




void dfsUtil(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& tree) 
{
    visited[u] = true;
    for (int v = 0; v < adjMatrix.size(); ++v) 
    {
        if (adjMatrix[u][v] && !visited[v]) 
        {
            tree[u][v] = 1;
            tree[v][u] = 1; 
            dfsUtil(v, adjMatrix, visited, tree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) 
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> tree(n, vector<int>(n, 0));
    dfsUtil(start, adjMatrix, visited, tree);
    return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) 
{
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) 
    {
        int u = q.front(); 
        q.pop();
        for (int v = 0; v < n; ++v) 
        {
            if (adjMatrix[u][v] && !visited[v]) 
            {
                visited[v] = true;
                tree[u][v] = tree[v][u] = 1;
                q.push(v);
            }
        }
    }
    return tree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int cur = q.front(); 
        q.pop();
        if (cur == v) return true;
        for (int i = 0; i < n; ++i) 
        {
            if (adjMatrix[cur][i] && !visited[i]) 
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    pq.push({ 0, start });
    while (!pq.empty()) 
    {
        pair<int, int> top_element = pq.top(); 
        int d = top_element.first; 
        int u = top_element.second;
        pq.pop();
        if (d > dist[u]) continue;
        for (int v = 0; v < n; ++v) 
        {
            if (adjMatrix[u][v] && dist[v] > dist[u] + adjMatrix[u][v]) 
            {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return path;
    for (int v = end; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[start] = 0;

    for (int i = 0; i < n - 1; ++i) 
    {
        for (int u = 0; u < n; ++u) 
        {
            for (int v = 0; v < n; ++v) 
            {
                if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) 
                {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; ++u) 
    {
        for (int v = 0; v < n; ++v) 
        {
            if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) 
            {
                return {}; // chu trinh -
            }
        }
    }
    vector<int> path;
    if (dist[end] == INT_MAX) return path; 
    for (int v = end; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}



bool isConnectedUndirected(const vector<vector<int>>& graph) 
{
    int n = graph.size();
    vector<bool> visited(n, false);
    int start = -1;
    for (int i = 0; i < n; ++i)
        if (accumulate(graph[i].begin(), graph[i].end(), 0) > 0) 
        {
            start = i;
            break;
        }

    if (start == -1) return true; 

    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) 
    {
        int u = s.top(); s.pop();
        for (int v = 0; v < n; ++v) 
        {
            if (graph[u][v] && !visited[v]) 
            {
                visited[v] = true;
                s.push(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        int deg = accumulate(graph[i].begin(), graph[i].end(), 0);
        if (deg > 0 && !visited[i])
            return false;
    }
    return true;
}
vector<int> findEulerCycleSafe(vector<vector<int>> graph) 
{
    int n = graph.size();
    for (int i = 0; i < n; ++i) 
    {
        int deg = accumulate(graph[i].begin(), graph[i].end(), 0);
        if (deg % 2 != 0)
            return {}; 
    }

    if (!isConnectedUndirected(graph))
        return {};

    vector<int> path;
    stack<int> st;
    st.push(0);

    while (!st.empty()) 
    {
        int u = st.top();
        bool hasEdge = false;
        for (int v = 0; v < n; ++v) 
        {
            if (graph[u][v]) 
            {
                hasEdge = true;
                st.push(v);
                graph[u][v] = graph[v][u] = 0;
                break;
            }
        }
        if (!hasEdge) 
        {
            path.push_back(u);
            st.pop();
        }
    }
    int originalEdges = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (graph[i][j])
                ++originalEdges;

    if (path.size() != originalEdges + 1)
        return {};

    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    return 0;
}