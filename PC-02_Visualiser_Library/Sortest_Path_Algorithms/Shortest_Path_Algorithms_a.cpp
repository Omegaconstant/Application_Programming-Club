/*  
Shortest Path Algorithm: A
Problem: Single source-Single destination shortest path in a Simple (Un)Directed & Unweighted Graph
Algorithm: BFS
Time Complexity: O(|V| +|E|)
Space Complexity: O(|V| +|E|) +3*O(|N|)
*/


/* 
Input Format:
The first line contains one integer t — the number of test cases.
Then t test cases follow, each being characterised as follws:
1st Line contains two integers n, m — No. of nodes (0-based indexing) and No. of edges.
Then m lines follws w/- each line containing 2 integers x & y, if there is an edge from x to y.
Then one line follows representing two integers source u & destination v.
*/


/*
Output Format:
Display Test case No.
If no such path exits, display '∃ no uv-Path.'
If such a path exists of minimum cost, specify path length & the path.
*/


/*
Sample I/P:
2
5 6
0 1 
0 4
1 4
1 3
4 3
3 2
0 2
3 1
0 1
0 2


Sample O/P:
Case #1: 
Minimum uv-Path Length : 3
Path:
0 1 3 2 

Case #2: 
∃ no uv-Path.
*/


#include <bits/stdc++.h>
using namespace std;


long long int n;  // No. of nodes
long long int m;  // No. of edges
vector<vector<long long int>> Adj;  // Adjacency list Adj


void BFS(long long int u, long long int v){
    if (u == v)
    {
        cout << "Minimum uv-Path Length : " << 0 << endl
             << "Path :" << endl;
        cout << u << endl;
        cout << endl;
        return;
    }
    vector<long long int> PrevNode(n, -1);  // PrevNode Matrix to store the previous Adjacent node wrt current node
    // vector<long long int> bfspath;          // Matrix bfspath to store the visited nodes

    queue<long long int> q;  // Queue q to store the nodes to be proessed
    q.push(u);               // Insert u to q
    PrevNode[u] = -2;        // Mark the PrevNode of vertex u as -2

    // Run the loop till queue is not empty or vertex v has not been reached
    while (q.empty() == 0 && PrevNode[v] == -1)
    {
        long long int node = q.front();  // Current Node of consideration
        q.pop();                         // Remove it from queue
        // bfspath.push_back(node);         // Store it in bfspath

        for (auto i: Adj[node])     // For all Adjacent Vertices of concerned Node
        {
            if (PrevNode[i] == -1)   // If it has not been visited
            {
                q.push(i);           // Add it to Queue
                PrevNode[i] = node;  // Mark PrevNode of that node by the previous Adjacent node,i.e. concerned Node
            }
        }
    }

    if (PrevNode[v] == -1)  // If vertex v has not been reached => u & v are in different components OR v has 0-in degree OR u has 0-out degree
    {
        cout << "∃ no uv-Path." << endl;  // There exists no uvPath
        cout << endl;
        return;
    }

    vector<long long int> uvPath;  // Matrix uvPath to store the shorted uvPath
    long long int vertex = v;      // Start from vertex v

    while (vertex != u)  // Until vertex is u
    {
        uvPath.push_back(vertex);   // Update the uvPath
        vertex = PrevNode[vertex];  // Update current vertex
    }
    uvPath.push_back(u);  // Add vertx u to uv path

    reverse(uvPath.begin(), uvPath.end());  // Get the uv path

    // Show the path length
    cout << "Minimum uv-Path Length : " << uvPath.size() - 1 << endl
         << "Path:" << endl;

    // Show the path
    for (auto i: uvPath)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;
    return;
}


int32_t main()
{
    ios_base::sync_with_stdio(0);  // Disable synchronization btwn C & C++ std streams

    cin.tie(0);   // Untie cin from cout
    cout.tie(0);  // Untie cout from cin

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
            long long int x, y;  // We have an xy edge
            cin >> x >> y;

            Adj[x].push_back(y);  // Assumption : 0-based indexing
            // Adj[y].push_back(x);  // Incase of Undirected, uncomment this line  
        }

        long long int u, v;  // The start & end vertex of the path
        cin >> u >> v;

        BFS(u,v);  // Call BFS
    }
    return 0;
}