/*
Stable Marriage Problem
Algorithm: Gale–Shapley algorithm
Time Complexity: O(nm)
Space Complexity: O(nm)
*/


/*
Input Format:
The first line contains one integer t — the number of test cases.
Then t test cases follow, each being characterised as follws:
1st Line contains two integers n, m — No. of men and No. of wpmen.
Then n lines follws w/- each line containing m integers: the prefernce list of ith man (all intergers lie between 0 and m-1 inclusively) 
Then m lines follws w/- each line containing n integers: the prefernce list of jth woman (all intergers lie between 0 and n-1 inclusively) 
*/


/*
Output Format:
Display Test case No.
Display the solution is optimal for which community
Display Man & Woman Column & Show a single soultion all stable pairs 
*/

/*
Sample I/P:
2

3 2

0 1
1 0
0 1

0 1 2
2 0 1 
 
4 4

0 1 2 3 
1 2 3 0
2 3 0 1 
3 0 1 2 

0 1 2 3 
1 2 3 0 
2 3 0 1 
3 0 1 2

Sample O/P:
Case #1: 
Stable Marriage w/- Women Optimal Solution: 
Man X Woman 
0 X 0
2 X 1

Case #2: 
Stable Marriage w/- Men Optimal Solution: 
Woman X Man 
0 X 0
1 X 1
2 X 2
3 X 3
*/


#include <bits/stdc++.h>
using namespace std;


long long int n;                                    // No. of men
long long int m;                                    // No. of women
vector<vector<long long int>> MenPreferenceList;    // Preference list of Men
vector<vector<long long int>> WomenPreferenceList;  // Preference list of Women
vector<vector<long long int>> choiceNo;             // Matrix Choice no. to store the choice no. of jth Proposer as per ith Selector
vector<long long int> marriage;                     // Final marraige matrix w/- index being Selector & index element being their Worst possible partner.


// Whether Selector S prefers Person1 Over Person2
bool SPreferP1OverP2(long long int S, long long int P1, long long int P2)
{
    if (choiceNo[S][P1] < choiceNo[S][P2])
        return 1; // Selector does so if it has a higher Perf. for Person1
    return 0;
}


void StableMarriage()
{
    cin >> n >> m;

    MenPreferenceList.clear();                                // Clear MenPreferenceList
    MenPreferenceList.resize(n, vector<long long int>(m));    // Resize MenPreferenceList
    WomenPreferenceList.clear();                              // Clear WomenPreferenceList
    WomenPreferenceList.resize(m, vector<long long int>(n));  // Resize WomenPreferenceList

    // Take MenPreferenceList from user
    for (long long int i = 0; i < n; i++)
    {
        for (long long int j = 0; j < m; j++)
        {
            cin >> MenPreferenceList[i][j];
        }
    }

    // Take WomenPreferenceList from user
    for (long long int i = 0; i < m; i++)
    {
        for (long long int j = 0; j < n; j++)
        {
            cin >> WomenPreferenceList[i][j];
        }
    }

    marriage.clear();                // Clear marriage
    marriage.resize(max(n, m), -1);  // Reinitialise marriage

    // If No. of men > No. of Women
    bool MenLarger = (n > m);                 // MenLarger is 1 otherwise 0
    long long int Max = (MenLarger) ? n : m;  // Get which Sex is in max no.
    long long int Min = (MenLarger) ? m : n;  // Get which Sex is in min no.

    choiceNo.clear();                                  // Clear Matrix choiceNo
    choiceNo.resize(Max, vector<long long int>(Min));  // Resize Matrix choiceNo
    /*
    Choice No. is from perception of Selector, it is the rank that ith selector gives to jth person of other Sex
    Hence dimension is Max*Min, Since we assume the Sex who is low in no. proposes
    */

    // Get the choiceNo matrix
    for (long long int i = 0; i < Max; i++)
    {
        long long int mark = 0;
        for (long long int j = 0; j < Min; j++)
        {
            if (MenLarger)
            {
                choiceNo[i][MenPreferenceList[i][j]] = mark++;
            }
            else
            {
                choiceNo[i][WomenPreferenceList[i][j]] = mark++;
            }
        }
    }

    vector<queue<long long int>> ProposerPreferenceList(Min);  // Matrix of Queue ProposerPreferenceList to keep track of the selector left to be proposed by ith proposer

    // Construct ProposerPrefernceList
    if (MenLarger)
    {
        for (long long int i = 0; i < Min; i++)
        {
            queue<long long int> x;
            for (long long int j = 0; j < Max; j++)
            {
                x.push(WomenPreferenceList[i][j]);
            }
            ProposerPreferenceList[i] = x;
        }
    }
    else
    {
        for (long long int i = 0; i < Min; i++)
        {
            queue<long long int> x;
            for (long long int j = 0; j < Max; j++)
            {
                x.push(MenPreferenceList[i][j]);
            }
            ProposerPreferenceList[i] = x;
        }
    }

    queue<long long int> FreeProposer; // Queue FreeProposer to keep the record of current & successive proposers
    
    // Insert all persons of the minor community to the Queue FreeProposer
    for (long long int i = 0; i < Min; i++)
    {
        FreeProposer.push(i);
    }

    // Until there No more Free Proposer, which means all proposers got engaged
    while (FreeProposer.size() > 0)
    {

        // Take the 1st Proposer
        long long int Proposer = FreeProposer.front();
        FreeProposer.pop();

        // Check it's top Preference whom it has not proposed yet
        long long int Selector = ProposerPreferenceList[Proposer].front();
        ProposerPreferenceList[Proposer].pop();

        // If that selector is free
        if (marriage[Selector] == -1)
        {
            marriage[Selector] = Proposer;  // Tentatively engage both 2
            continue;                       // Go to start of the loop
        }

        // If that Selector has a Partner
        long long int CurrentPartner = marriage[Selector];

        // Check if selector prefers current proposer than current partner
        if (SPreferP1OverP2(Selector, Proposer, CurrentPartner))
        {
            marriage[Selector] = Proposer;      // If so add current partner to the freeproposer queue
            FreeProposer.push(CurrentPartner);  // Make tentative engagement btwn proposer & selector
        }
        else // If not
        {
            FreeProposer.push(Proposer);  // Add proposer to the end of the queue
        }
    }

    // Show the marriage matrix
    // Show only those <index, element> pairs which are not -1
    long long int ans = 0;
    if (MenLarger)
    {
        cout << "Stable Marriage w/- Women Optimal Solution: \n";
        cout << "Man X Woman \n";
        for (long long int i = 0; i < Max; i++)
        {
            if (marriage[i] != -1)
            {
                cout << i << " X " << marriage[i] << endl;
                ans++;
            }
        }
    }
    else
    {
        cout << "Stable Marriage w/- Men Optimal Solution: \n";
        cout << "Woman X Man \n";
        for (long long int i = 0; i < Max; i++)
        {
            if (marriage[i] != -1)
            {
                cout << i << " X " << marriage[i] << endl;
                ans++;
            }
        }
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

    long long int n = t;
    while (t--)
    {
        cout << "Case #" << n - t << ": \n";  // Display Case No.
        StableMarriage();
    }
    return 0;
}