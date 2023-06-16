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

int get_sign(int a)
{
    if (a > 0)
    {
        return 1;
    }
    else if (a < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

const int N = 100102;
int f1[N], f2[N];

int query(int *f, int n)
{
    int a = 0;
    for (int i = n; i > 0; i -= (i & -i))
        a += f[i];
    return a;
}

void upd(int *f, int i, int v)
{
    for (; i <= N; i += (i & -i))
        f[i] += v;
}

void revert(int *fn, int *fz, int pos, int prev)
{
    if (prev == 0)
    {
        // printf("revert zero to %d\n",pos);
        // reduce zero tree
        upd(fz, pos, -1);
    }
    else if (get_sign(prev) < 0)
    {
        // printf("revert neg to %d\n",pos);
        // reduce if negative
        upd(fn, pos, -1);
    }
}

void insert(int *fn, int *fz, int pos, int val)
{
    if (val == 0)
    {
        // printf("insert zero to %d\n",pos);
        upd(fz, pos, 1);
    }
    else if (val < 0)
    {
        // printf("insert neg to %d\n",pos);
        upd(fn, pos, 1);
    }
}

int main()
{
    int n, k;
    while (cin >> n >> k)
    {
        memset(f1, 0, N);
        memset(f2, 0, N);
        vi prev(n, 0);
        repp(x, 1, n)
        {
            int a;
            cin>>a;
            // scanf("%d", &a);
            // printf("%d\n", a);
            prev[x] = get_sign(a);
            insert(f1, f2, x, prev[x]);
        }
        repp(x, 1, k)
        {
            string cmd;
            int a, b;
            // printf("test\n");
            cin>>cmd>>a>>b;
            // scanf("%s %d %d", &cmd, &a, &b);
            // printf("%s %d %d",cmd,a,b);
            if (cmd[0] == 'C')
            {
                // update
                int val = get_sign(b);
                if (val == prev[a])
                {
                    // same sign, skip
                    continue;
                }
                else
                {
                    // revert old value
                    revert(f1, f2, a, prev[a]);
                    insert(f1, f2, a, val);
                    prev[a]=val;
                }
            }
            else
            {
                // printf("Case %d: %d %d: ",x,query(f2,b)-query(f2,a-1),query(f1,b)-query(f1,a-1));
                // answer query
                if (query(f2, b) - query(f2, a - 1) != 0)
                {
                    // got zero
                    cout<<"0";
                    // printf("0");
                }
                else
                {
                    int negcnt = query(f1, b) - query(f1, a - 1);
                    if (negcnt % 2 == 0)
                    {
                        // even number of -
                        cout<<"+";
                        // printf("+");
                    }
                    else
                    {
                        // printf("-");
                        cout<<"-";
                    }
                }
                // printf("\n");
            }
        }
        cout<<"\n";
        // printf("\n");
    }
    return 0;
}

/*
4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
5 9
1 5 -2 4 3
P 1 2
P 1 5
C 4 -5
P 1 5
P 4 5
C 3 0
P 1 5
C 4 -5
C 4 -5
*/