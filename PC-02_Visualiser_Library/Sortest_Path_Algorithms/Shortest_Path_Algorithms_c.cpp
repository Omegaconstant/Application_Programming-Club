/*
Shortest Path Algorithm : C
Problem: Single source-Single destination shortest path in a Simple (Un)Directed & Generalised Weighted Graph
Algorithm: Bellman-Ford Algorithm
Time Complexity: 2*O(|V||E|)
Space Complexity: O(|V|+|E|) + 3*O(|N|)
*/


/*
Input Format:
The first line contains one integer t — the number of test cases.
Then t test cases follow, each being characterised as follws:
1st Line contains two integers n, m — No. of nodes (0-based indexing) and No. of edges.
Then m lines follws w/- each line containing 3 integers x, y & w, if there is an edge from x to y & it's weight w.
Then one line follows representing two integers source u & destination v.
*/


/*
Output Format:
Display Test case No.
If no such path exits, display '∃ no uv-Path.'
If there is a Negative Cycle, Mention it & Specify if it affects the minimum uvPath cost.
If such a path exists of finite minimum cost, specify path cost & the path.
*/


/*
Sample I/P:
3
5 5
0 1 1
1 2 2
3 0 10
2 3 -2
2 4 3
0 4
3 3
0 1 2
2 0 -3
1 2 -8
2 0
5 5
0 1 1
1 2 2
2 3 -10
3 4 5
4 2 1
0 1


Sample O/P:
Case #1: 
Minimum uv-Path Cost : 6
Path :
0 1 2 4 

Case #2: 
∃ atleast one NEGATIVE CYCLE making uv-Path cost to be arbitrarily low.

Case #3: 
∃ atleast one NEGATIVE CYCLE w/o altering minimum uv-Path cost.
Minimum uv-Path Cost : 1
Path :
0 1
*/


#include <bits/stdc++.h>
using namespace std;


long long int n;                                         // No. of nodes
long long int m;                                         // No. of edges
vector<vector<pair<long long int, long long int>>> Adj;  // Adjacency list Adj


void BellmanFord(long long int u, long long int v)
{
    vector<long long int> PrevNode(n, -1);  // PrevNode Matrix to store the previous Adjacent node wrt current node
    vector<long long int> dist(n, 1e18);    // Matrix dist to store minimum distance of a Node from u
    PrevNode[u] = -2;                       // Mark the PrevNode of vertex u as -2
    dist[u] = 0;                            // Distance of Node u from itself costs 0 weights


    // Relax all edges repeatedly for n-1 times
    for (long long int i = 0; i < n; i++)   // Run th Cycle for n-1 times
    {
        for (long long int j = 0; j < n; j++)  // For each index j in Set of Nodes
        {
            for (long long int k = 0; k < Adj[j].size(); k++)  // Go through the Adjacency list of node j
            {
                if (dist[j] + Adj[j][k].second < dist[Adj[j][k].first])  // Relax the neighbouring Node if there is a better path
                {
                    dist[Adj[j][k].first] = dist[j] + Adj[j][k].second;  // Update dist[Neighbour]
                    PrevNode[Adj[j][k].first] = j;  // Update PrevNode[Neighbour]
                }
            }
        }
    }

    long long int CurrentDistance = dist[v];  // Store the current minimum possible cost for v
    
    // Check for NeEGATIVE CYCLE and it's effect
    bool check = 0;
    for (long long int i = 0; i < n; i++)
    {
        for (long long int j = 0; j < n; j++)
        {
            for (long long int k = 0; k < Adj[j].size(); k++)
            {
                if (dist[j] + Adj[j][k].second < dist[Adj[j][k].first])  // If we have a better path at any instance
                {
                    dist[Adj[j][k].first] = dist[j] + Adj[j][k].second;
                    PrevNode[Adj[j][k].first] = j;
                    check = 1;  // We just encountered a NEGATIVE CYCLE
                }
            }
        }
    }
    long long int UpdatedDistance = dist[v];  // UpdatedDistcnce to v after the check for NEGATIVE CYCLE

    if (PrevNode[v] == -1)  // If vertex v has not been reached => u & v are in different components OR v is a Source OR u is a Sink
    {
        cout << "∃ no uv-Path." << endl;  // There exists no uvpath
        cout << endl;
        return;
    }

    if (check == 1)  // If we have a NEGATIVE CYCLE
    {
        if (CurrentDistance != UpdatedDistance)  // If both the distances before and after the check are not same. 
        {
            cout << "∃ atleast one NEGATIVE CYCLE making uv-Path cost to be arbitrarily low." << endl;
            cout << endl;
            return;
        }
        else  // If both are the same
        {
            cout << "∃ atleast one NEGATIVE CYCLE w/o altering minimum uv-Path cost." << endl;
        }
    }

    vector<long long int> uvpath;  // Matrix uvpath to store the shorted uvpath
    long long int vertex = v;      // Start from vertex v

    while (vertex != u)  // Until vertex is u
    {
        uvpath.push_back(vertex);   // Update the uvpath
        vertex = PrevNode[vertex];  // Update current vertex
    }
    uvpath.push_back(u);  // Add vertx u to uv path

    reverse(uvpath.begin(), uvpath.end());  // Get the uv path

    // Show the path Cost
    cout << "Minimum uv-Path Cost : " << dist[v] << endl
         << "Path :" << endl;

    // Show the path
    for (auto i : uvpath)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;
    return;

}


int32_t main()
{
    ios_base::sync_with_stdio(false);  // Disable synchronization btwn C & C++ std streams

    cin.tie(NULL);   // Untie cin from cout
    cout.tie(NULL);  // Untie cout from cin

    // No. of test cases
    long long int t;
    cin >> t;

    long long int p = t;
    while (t--)
    {
        cout << "Case #" << p - t << ": \n";  // Display Case No.
                cin >> n >> m;

        Adj.clear();    // Clear Adj
        Adj.resize(n);  // Resize Adj

        /* Store the input graph in Adjacency list v */
        for (long long int i = 0; i < m; i++)
        {
            long long int x, y, w;  // We have an xy edge
            cin >> x >> y >> w;

            Adj[x].push_back(make_pair(y, w));
        }

        long long int u, v;  // The start & end vertex of the path
        cin >> u >> v;
        BellmanFord(u, v);  // Call BellmanFord
    }
    return 0;
}