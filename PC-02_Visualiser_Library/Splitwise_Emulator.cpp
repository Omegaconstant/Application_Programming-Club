/*
Splitwise Emulator
Algorithm: Constructive & Implementation
Time Complexity: O(max(|V|log|V|,|E|))
Space Complexity: O(|V|+|E|) 
*/


/* 
Input Format:
The first line contains one integer t — the number of test cases.
Then t test cases follow, each being characterised as follws:
1st Line contains two integers n, m — No. of nodes (0-based indexing) and No. of edges.
Then m lines follws w/- each line containing 3 integers x, y & w, if there is an edge from x to y & it's weight w.
*/


/*
Output Format:
Display Test case No.
1st Line contains two integers n, m' — No. of nodes (0-based indexing) and No. of new edges.
Then m' lines follws w/- each line containing 3 integers x', y' & w', if there is an edge from x' to y' & it's weight w'.
All nodes are either sink or source.
*/


/*
Sample I/P:
1
3 3
0 1 2
1 2 14 
2 0 45


Sample O/P:
Case #1: 
3 2
1 0 12
2 0 31
*/


#include <bits/stdc++.h>
using namespace std;


void SplitwiseEmulator()
{
    long long int n;  // No. of nodes
    long long int m;  // No. of edges
    cin >> n >> m;

    vector<vector<pair<long long int, long long int>>> Adj(n);  // Adjacency list Adj
    vector<pair<long long int, long long int>> NetDebt(n);      // Net debt matrix NetDebt
    
    for (long long int i = 0; i < n; i++)
        NetDebt[i] = make_pair(i, 0);

    /* Store the input Graph in Adjacency List Adj & Update matrix NetDebt */
    for (long long int i = 0; i < m; i++)
    {
        long long int x, y, w;
        cin >> x >> y >> w;

        Adj[x].push_back(make_pair(y, w));  // Assumption : 0-based indexing
        NetDebt[y].second -= w;  // Decrement net debt amount by w of the node to which the arc points
        NetDebt[x].second += w;  // Increment net debt amount by w of the node from which the arc points
    }

    vector<vector<long long int>> Graph;  // Edge list of Final Graph w/- only sources & sinks

    /* Sort NetDebt matrix according to individual net debt */
    sort(NetDebt.begin(), NetDebt.end(), 
        [&](const pair<long long int, long long int> a, const pair<long long int, long long int> b)
        { 
            return a.second < b.second; 
        });  // Sort matrix NetDebt as per increasing order of net debt of nodes

    long long int K1 = 0, K2 = n - 1;  // Two pointer K1 & K2

    /* Construct the Graphwer Graph */
    while (K1 < K2)
    {
        // Node 1: Node corresponding to pointer K1
        // Node 2: Node corresponding to pointer K2

        /* Update the pointer if the corresponding node has net debt 0 */
        if (NetDebt[K1].second == 0 && NetDebt[K2].second == 0) // If both Node have net debt 0
        {
            K1++;      // Update pointer K1
            K2--;      // Update pointer K2
            continue;  // Goto start of the loop
        }

        if (NetDebt[K1].second == 0)  // If Node 1 has net debt 0
        {
            K1++;      // Update pointer K1
            continue;  // Goto start of the loop
        }

        if (NetDebt[K2].second == 0)  // If Node 2 has net debt 0
        {
            K2--;      // Update pointer K2
            continue;  // Goto start of the loop
        }

        /* If both corresponding node have nonzero net debt */
        if (NetDebt[K1].second < 0 && NetDebt[K2].second > 0)
        {
            if (abs(NetDebt[K1].second) > abs(NetDebt[K2].second))  // If Node 1 has more net surplus than the net debt of Node 2
            {
                Graph.push_back({NetDebt[K2].first, NetDebt[K1].first, NetDebt[K2].second}); // Node 2 has an equivalent debt of net debt(Node 2) from Node 1

                NetDebt[K2].second = 0;               // Net debt of Node 2 becomes 0
                NetDebt[K1].second += NetDebt[K2].second;  // Net surplus of Node 1 (which is >0) reduces by net debt of Node 2

                K2--;      // Update pointer K2
                continue;  // Goto start of the loop
            }
            if (abs(NetDebt[K1].second) < abs(NetDebt[K2].second))  // If Node 1 has less net surplus than the net debt of Node 2
            {
                Graph.push_back({NetDebt[K2].first, NetDebt[K1].first, abs(NetDebt[K1].second)});  // Node 2 has an equivalent debt of net surplus(Node 1) from Node 1

                NetDebt[K1].second = 0;                    // Net surplus of Node 1 becomes 0
                NetDebt[K2].second -= abs(NetDebt[K1].second);  // Net debt of Node 2 (which is >0) reduces by net surplus of Node 1

                K1++;      // Update pointer K1
                continue;  // Goto start of the loop
            }

            // If Node 1 has the same net surplus as the net debt of Node 2
            Graph.push_back({NetDebt[K2].first, NetDebt[K1].first, NetDebt[K2].second});  // Node 2 has an equivalent debt of net surplus(Node 1) from Node 1

            NetDebt[K1].second = 0;  // Net surplus of Node 1 becomes 0
            NetDebt[K2].second = 0;  // Net debt of Node 2 becomes 0

            K1++;  // Update pointer K1
            K2--;  // Update pointer K2
        }
    }
    sort(Graph.begin(), Graph.end(),
        [&](const vector<long long int> a, const vector<long long int> b)
        {
            return a[0] < b[0];
        });  // Sort the Graph as per increasing order of 1st Node

    cout << n << " " << Graph.size() << endl;         // Display the modified Graph order and modified Graph size
    for (long long int i = 0; i < Graph.size(); i++)  // Show the edge list
    {
        // Node 1, Node 2, Weight w (There is an arc from Node 1 to Node 2 of weight w)
        cout << Graph[i][0] << " " << Graph[i][1] << " " << Graph[i][2] << endl;
    }
    cout << endl;  // Insert a blank line
}


int32_t main()
{
    ios_base::sync_with_stdio(0);  // Disable synchronization btwn C & C++ std streams

    cin.tie(0);   // Untie cin from cout
    cout.tie(0);  // Untie cout from cin

    // No. of test cases
    long long int t;
    cin >> t;

    long long int n = t;
    while (t--)
    {
        cout << "Case #" << n - t << ": \n";  // Display Case No.
        SplitwiseEmulator();
    }
    return 0;
}