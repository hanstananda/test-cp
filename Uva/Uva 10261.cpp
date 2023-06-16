// Input Output
#include <cstdio>
#include <cstdlib>
#include <iostream>
// Datastructures
#include <cstring>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <utility>
#include <queue>
// Others
#include <cmath>
#include <numeric> // std::iota
#include <algorithm>
#include <time.h>
// Define
#define mp make_pair
#define ff first
#define fi first
#define ss second
#define se second
#define pb push_back
#define eb emplace_back
#define rep(x, a, b, c) for (int x = a; x <= b; x += c)
#define repp(x, a, b) rep(x, a, b, 1)
#define rev(x, a, b, c) for (int x = a; x >= b; x -= c)
#define revv(x, a, b) rev(x, a, b, 1)

using namespace std;

// Typedef
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<vi> vvi;
typedef long long ll;
typedef unsigned long long ull;

// const
const double EPS = 1e-9;
const double PI = acos(-1);
const int MOD = 1e9 + 7;
const int OO = 2e9;
const ll INF = (ll)9e18;

// Additional typedef for long long
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
typedef vector<pll> vll;
typedef vector<vector<pii>> vvii;


vi ships;
int memo[200][10001];
bool leftSide[200][10001];
int lim;
int dp(int pos, int left, int right)
{
    if (pos == ships.size())
    {
        // all taken
        return 0;
    }
    if (left<=0 && right<=0) return 0; // cannot take anymore 
    int curLength = ships[pos];
    // results in memo
    // We only need to memo 1 of the space used since total space used at idx is always the same, 
    // thus we can just use one of them as reference and disregard the rest (0/1 knapsack)
    if (memo[pos][left]!=-1)
    {
        return memo[pos][left];
    }
    
    int resLeft = 0, resRight = 0;
    if (curLength <= left)
    {
        // consider take left
        resLeft = dp(pos + 1, left - curLength, right) + 1; // take the ship to left
    }
    if (curLength <= right)
    {
        // consider take right
        resRight = dp(pos + 1, left, right - curLength) + 1; // take the ship to right
    }

    int res, choice;
    if (resLeft >= resRight)
    {
        res = resLeft;
        leftSide[pos][left]=true;
    }
    else
    {
        res = resRight;
    }
    // printf("%d %d %d: %d \n", pos, left, right, res);
    memo[pos][left] = res;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    // scanf("%d", &tc);
    cin>>tc;
    while (tc--)
    {
        // scanf("%d", &lim);
        cin>>lim;
        lim *= 100;
        ships.clear();
        do
        {
            int in;
            // scanf("%d", &in);
            cin>>in;
            if (in == 0)
            {
                break;
            }
            ships.pb(in);
        } while (1);
        int n = ships.size();
        // process
        memset(memo,-1,sizeof(memo));
        memset(leftSide,0,sizeof(leftSide));
        int ans = dp(0, lim, lim);
        // printf("%d\n", ans);
        cout<<ans<<"\n";
        // O(n) traceback
        int curLeft = lim;
        vector<string> backTrack;
        for(int x=0;x<ans;x++)
        {
            if (leftSide[x][curLeft]) { // Use left side
                backTrack.pb("port");
                curLeft -=  ships[x];
            } else { // right
                backTrack.pb("starboard");
            }
        }
        for(int i=0;i<backTrack.size();i++) {
            cout<<backTrack[i]<<"\n";
        }
        if(tc>0) {
            cout<<"\n";
        }
        
    }
    return 0;
}

/*
2
50
2500
3000
1000
1000
1500
700
800
0
50
2500
3000
1000
1000
1500
700
800
0
*/