/*
Minesweeper 2.0
Algorithm: BFS
Time Complexity: O(nm)
Space Complexity: O(nm)
*/


/*
Input Format:
The first line contains one integer t — the number of test cases.
Then t test cases follow, each being characterised as follws:
1st Line contains two integers n, m — No. of rows and No. of columns.
Then n lines follws w/- each line containing m space separated characters each being either _ or #
Then 2 line follows each line containing 2 interges, i.e. coordinate of source and destination in 0-based Indexing.
*/


/*
Output Format:
Display Test case No.
If no such path exits, display 'IMPOSSIBLE'
If such a path exists, mention minimum no. of steps, specify the path by showing the entire grid and by Marking path by 1, source by S and destination by D.
*/ 


/*
Sample I/P:
2
16 3 
_ _ _ 
_ # _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ # 
_ _ _ 
# _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ # 
6 1 
8 0
6 8 
_ # # # _ _ # # 
# _ # _ # # # # 
# # # _ # # # # 
_ _ # _ _ # # # 
# # # # # # # _ 
# _ # # # # _ # 
3 0 
0 0 


Sample O/P:
Case #1: 
Minimum No. Of Steps: 3
_ _ _ 
_ # _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ S _ 
_ 1 _ 
D 1 _ 
_ _ # 
_ _ _ 
# _ _ 
_ _ _ 
_ _ _ 
_ _ _ 
_ _ # 

Case #2: 
IMPOSSIBLE
*/


#include <bits/stdc++.h>
using namespace std;


long long int n,m;  // n: No. of rows, m: No. of columns
vector<vector<char>> Matrix;  // The 2D Grid


void Minesweeper(pair<long long int, long long int> s, pair<long long int, long long int> d)
{
    if (Matrix[d.first][d.second] == '#')  // If destination itself is an obstacle
    {
        cout << "IMPOSSIBLE" << endl << endl;  // It is impossible to find a path
        return;
    }
	
    if (Matrix[s.first][s.second] == '#')  // If source itself is an obstacle
    {
        cout << "IMPOSSIBLE" << endl << endl;  // It is impossible to find a path
        return;
    }

    if (s == d)  // If source & destination cell are the same
    {
        Matrix[d.first][d.second] = 'D';  // Denote the cell as 'D'
        cout << "Minimum no. of steps: 0" << endl;

        for (auto x : Matrix)
        {
            for (auto y : x)
                cout << y << " ";
            cout << endl;
        }
        return;
    }

	// Matrix Mark to store the minimun constrained distance of one cell from source
    vector<vector<long long int>> Mark(n, vector<long long int>(m));                                            
    
	// Matrix Index to store the record of previous nearby cell
	vector<vector<pair<long long int, long long int>>> Index(n, vector<pair<long long int, long long int>>(m));    

	queue<pair<long long int, long long int>> q;  // Queue q to store the temporary variable of the process
    bool flag = 0;                                // flag to check whether we reached destination or not

    long long int z = 1;           // Variable z to keep track of current distance in the process from source
    Mark[s.first][s.second] = -1;  // Set Mark of source to -1
    Index[s.first][s.second] = make_pair(-1,-1);  // Set Index of source to <-1, -1>

    /* update queue q, matrix Mark & Index for 1st movement */
    // Right cell
    if (s.first + 1 < n && Matrix[s.first + 1][s.second] == '_' && Mark[s.first + 1][s.second] == 0)
    {
        q.push(make_pair(s.first + 1, s.second));

        Mark[s.first + 1][s.second] = z;
        Index[s.first + 1][s.second] = s;
    }

    // Down cell
    if (s.second + 1 < m && Matrix[s.first][s.second + 1] == '_' && Mark[s.first][s.second + 1] == 0)
    {
        q.push(make_pair(s.first, s.second + 1));

        Mark[s.first][s.second + 1] = z;
        Index[s.first][s.second + 1] = s;
    }

    // Left cell
    if (s.first - 1 >= 0 && Matrix[s.first - 1][s.second] == '_' && Mark[s.first - 1][s.second] == 0)
    {
        q.push(make_pair(s.first - 1, s.second));

        Mark[s.first - 1][s.second] = z;
        Index[s.first - 1][s.second] = s;
    }

    // Up cell
    if (s.second - 1 >= 0 && Matrix[s.first][s.second - 1] == '_' && Mark[s.first][s.second - 1] == 0)
    {
        q.push(make_pair(s.first, s.second - 1));

        Mark[s.first][s.second - 1] = z;
        Index[s.first][s.second - 1] = s;
    }

    /* Iterate BFS */
    // Till q is not empty & destination has not been discovered
    while (q.empty() == 0 && flag == 0)
    {
        z++;                         // Update z
        long long int k = q.size();  // Store the no. of previously recorded cells

        /* Update queue q, matrix Mark & Index for zth movement */
        while (k--)
        {
            pair<long long int, long long int> p = q.front();  // Store the currently concerned cell

            // right cell
            if (p.first + 1 < n && Matrix[p.first + 1][p.second] == '_' && Mark[p.first + 1][p.second] == 0)
            {
                q.push(make_pair(p.first + 1, p.second));

                Mark[p.first + 1][p.second] = z;
                Index[p.first + 1][p.second] = p;
            }

            // down cell
            if (p.second + 1 < m && Matrix[p.first][p.second + 1] == '_' && Mark[p.first][p.second + 1] == 0)
            {
                q.push(make_pair(p.first, p.second + 1));

                Mark[p.first][p.second + 1] = z;
                Index[p.first][p.second + 1] = p;
            }

            // left cell
            if (p.first - 1 >= 0 && Matrix[p.first - 1][p.second] == '_' && Mark[p.first - 1][p.second] == 0)
            {
                q.push(make_pair(p.first - 1, p.second));

                Mark[p.first - 1][p.second] = z;
                Index[p.first - 1][p.second] = p;
            }

            // up cell
            if (p.second - 1 >= 0 && Matrix[p.first][p.second - 1] == '_' && Mark[p.first][p.second - 1] == 0)
            {
                q.push(make_pair(p.first, p.second - 1));

                Mark[p.first][p.second - 1] = z;
                Index[p.first][p.second - 1] = p;
            }

            q.pop();                           // Remove the cell from record
            if (Mark[d.first][d.second] != 0)  // If the destination has been reached
                flag = 1;                      // Update the flag
        }
    }

    if (flag == 0)  // If the destination has not been reached
    {
        cout << "IMPOSSIBLE" << endl;  // It is impossible to find a path
        return;
    }

    long long int st = Mark[d.first][d.second];                        // Store the no. of steps it took to reach destination
    pair<long long int, long long int> pr = Index[d.first][d.second];  // Store the previous cell
    cout << "Minimum No. Of Steps: " << st << endl;

    /* Show the path by Marking it '1'*/
    while (st--)
    {
        Matrix[pr.first][pr.second] = '1';     // Mark the previous cell to '1'
        pr = Index[pr.first][pr.second];  // Update the previous cell
    }

    /* Mark the source & destination */
    Matrix[s.first][s.second] = 'S';
    Matrix[d.first][d.second] = 'D';

    /* Show the grid */
    for (auto row: Matrix)
    {
        for (auto element : row)
            cout << element << " ";
        cout << endl;
    }
    cout << endl;
    
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

        Matrix.clear();  // Clear Matrix
        Matrix.resize(n, vector<char> (m));  // The 2-D Grid

        for (auto &x : Matrix)
        {
            for (auto &y : x)
                cin >> y;
        }

        pair<long long int, long long int> s, d;  // s: Source Cell, d: Destination Cell [Both in 0-based Indexing]
        cin >> s.first >> s.second;
        cin >> d.first >> d.second;

        Minesweeper(s,d);  // Call Minesweeper
    }

    return 0;
}
