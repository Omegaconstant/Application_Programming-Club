/*
Shortest Path Algorithm: B
Problem: Single source-Single destination shortest path in a Simple (Un)Directed & Non-negatively Weighted Graph
Algorithm: Dijkstra's Algorithm
Time Complexity: O(|E| +|V|*log(|V|))
Space Complexity: O(|V| +|E|) +4*O(|N|)
*/


/* 
Input Format:
The first line contains one integer t — the number of test cases.
Then t test cases follow, each being characterised as follws:
1st Line contains two integers n, m — No. of nodes (0-based indexing) and No. of edges.
Then m lines follws w/- each line containing 3 integers x, y & w, if there is an edge from x to y & it's weight w. (w>0)
Then one line follows representing two integers source u & destination v.
*/


/*
Output Format:
Display Test case No.
If no such path exits, display '∃ no uv-Path.'
If such a path exists of minimum cost, specify path cost & the path.
*/


/*
Sample I/P:
2
5 5 
0 1 1
0 4 1
1 4 3 
1 3 1
4 3 1
1 3
3 3
0 1 2
2 0 3
2 1 8
2 1


Smaple O/P:
Case #1: 
Minimum uv-Path Cost : 1
Path :
1 3 

Case #2: 
Minimum uv-Path Cost : 5
Path :
2 0 1
*/


#include <bits/stdc++.h>
using namespace std;


long long int n;  // No. of nodes
long long int m;  // No. of edges
vector<vector<pair<long long int, long long int>>> Adj;  // Adjacency list Adj


void Dijkstra(long long int u, long long int v){

    if (u == v)
    {
        cout << "Minimum uv-Path Length : " << 0 << endl
             << "Path :" << endl;
        cout << u << endl;
        cout << endl;
        return;
    }

    vector<long long int> PrevNode(n, -1);  // PrevNode Matrix to store the previous Adjacent node wrt current node
    vector<long long int> dist(n, 1e18);    // Matrix dist to store minimum distance of a Node from u

    // min heap Priority Queue pq to store the nodes to be proessed in <dist, Node> format
    priority_queue<pair<long long int, long long int>, vector<pair<long long int, long long int>>, greater<pair<long long int, long long int>>> pq; 
    pq.push(make_pair(0,u));             // Insert u to pq
    PrevNode[u] = -2;                    // Mark the PrevNode of vertex u as -2
    dist[u] = 0;                         // Distance of Node u from itself costs 0 weights

    // Run the loop till pq is not empty or vertex v has not been released
    while (pq.empty() == 0 && pq.top().second != v )
    {
        long long int node = pq.top().second;  // Current Node of consideration
        long long int cost = pq.top().first;   // Current distance of consideration
        pq.pop();                              // Remove it from priority_queue

        vector<pair<long long int, long long int>>:: iterator i;
        for (auto i: Adj[node])  // For all Adjacent Vertices of concerned Node
        {
            long long int vertex = i.first;     // Adjacent node of concerned node
            long long int distance = i.second;  // Weight of corresponding edge
            
            if (cost + distance < dist[vertex])  // If we have a better path via node
            {
                dist[vertex] = cost + distance;  // Update dist[vertex]
                pq.push(make_pair(dist[vertex], vertex));  // Add corresponding element to pq
                PrevNode[vertex] = node;  // Mark PrevNode of that node by the previous Adjacent node,i.e. concerned Node
            }
        }
    }

    if (PrevNode[v] == -1) // If vertex v has not been reached => u & v are in different components OR v is a Source OR u is a Sink
    {
        cout << "∃ no uv-Path." << endl; // There exists no uvPath
        cout << endl;
        return;
    }

    vector<long long int> uvPath; // Matrix uvPath to store the shorted uvPath
    long long int vertex = v;     // Start from vertex v

    while (vertex != u) // Until vertex is u
    {
        uvPath.push_back(vertex);  // Update the uvPath
        vertex = PrevNode[vertex]; // Update current vertex
    }
    uvPath.push_back(u); // Add vertx u to uv path

    reverse(uvPath.begin(), uvPath.end()); // Get the uv path

    // Show the path Cost
    cout << "Minimum uv-Path Cost : " << dist[v] << endl
         << "Path :" << endl;

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
    ios_base::sync_with_stdio(false); // Disable synchronization btwn C & C++ std streams

    cin.tie(NULL);  // Untie cin from cout
    cout.tie(NULL); // Untie cout from cin

    // No. of test cases
    long long int t;
    cin >> t;

    long long int p = t;
    while (t--)
    {
        cout << "Case #" << p - t << ": \n"; // Display Case No.
        cin >> n >> m;

        Adj.clear();    // Clear Adj
        Adj.resize(n);  // Resize Adj

        /* Store the input graph in Adjacency list v */
        for (long long int i = 0; i < m; i++)
        {
            long long int x, y, w;  // We have an xy edge
            cin >> x >> y >> w;

            Adj[x].push_back(make_pair(y, w));
            // Adj[y].push_back(make_pair(x, w));  // Incase of Undirected, uncomment this line
        }

        long long int u, v;  // The start & end vertex of the path
        cin >> u >> v;
        Dijkstra(u,v);  // Call Dijkstra
    }
    return 0;
}