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


const int N=200;
const int M=20100;
int memo[N][M];
bool thisSide[N][M];
int lim;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    // scanf("%d", &tc);
    cin>>tc;
    while (tc--)
    {
        // reset memo
        memset(memo,-1,sizeof(memo));
        memset(thisSide,0,sizeof(thisSide));

        // scanf("%d", &lim);
        cin>>lim;
        lim *= 100;
        vi ships;
        ships.clear();ships.pb(0); // placeholder to start index at 1
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
        memo[0][lim] = lim;
        for(int i=1;i< n; i++) {
            for(int j=0;j<=lim;j++) {
                if (memo[i-1][j]>=ships[i]) {
                    // try take on the other side
                    memo[i][j]= memo[i-1][j] - ships[i];
                }
                
                if (memo[i-1][j] >0 && j>= ships[i]) {
                    // try to take on this side 
                    memo[i][j-ships[i]] = memo[i-1][j];
                    thisSide[i][j-ships[i]]=1;
                }
                
            }
        }
        // backtrack to get the answer 
        int ans = 0;
        int lastPos = 0;
        for(int i=n-1;i>=1;i--) {
            for(int j=0;j<=lim;j++) {
                if(memo[i][j]>=0) {
                    ans=i;
                    lastPos= j;
                    break;
                }
            }
            if (ans>0) {
                break;
            }
        }

        vector<string> backTrack;
        backTrack.clear();
        for(int i=ans;i>=1;i--) {
            // cout<<"Lastpos is"<<lastPos<<",Memo value is "<<memo[i][lastPos]<<"\n";
            // if(memo[i-1][lastPos]!=-1 && memo[i-1][lastPos]-memo[i][lastPos]==ships[i]) {
            //     // use left side 
            //     backTrack.pb("port");
            // } else {
            //     lastPos += ships[i];
            //     backTrack.pb("starboard");
            // }
            if(memo[i][lastPos]==-1) {
                return 0;
            }

            // if(lastPos+ships[i] <= lim && memo[i-1][lastPos+ships[i]]==memo[i][lastPos]) {
            //     lastPos += ships[i];
            //     backTrack.pb("starboard");
            // } else {
            //     backTrack.pb("port");
            // }
            if(thisSide[i][lastPos]) {
                backTrack.pb("port");
                lastPos += ships[i];
            }else {
                backTrack.pb("starboard");
            }
        }
        cout<<ans<<"\n";
        for(int i=backTrack.size()-1;i>=0;i--) {
            cout<<backTrack[i]<<"\n";
        }
        cout<<"\n";
        
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

1
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