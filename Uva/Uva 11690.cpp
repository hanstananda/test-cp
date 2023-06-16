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
#include <numeric>      // std::iota
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
#define rep(x,a,b,c) for(int x=a;x<=b;x+=c)
#define repp(x,a,b) rep(x,a,b,1)
#define rev(x,a,b,c) for(int x=a;x>=b;x-=c)
#define revv(x,a,b) rev(x,a,b,1)

using namespace std;

// Typedef
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<vi> vvi;
typedef long long ll;
typedef unsigned long long ull;

// const
const double EPS = 1e-9;
const double PI = acos(-1);
const int MOD = 1e9+7;
const int OO = 2e9;
const ll INF = (ll)9e18;

// Additional typedef for long long
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vll;
typedef vector<vector<pii>> vvii;

class UnionFind 
{ // OOP style
	private: vi p, rank; // remember: vi is vector<int>
	public:
	UnionFind(int N) 
	{ 
		rank.assign(N, 0);
		p.assign(N, 0); 
		for (int i = 0; i <N; i++) 
		p[i] = i; 
	}
	int findSet(int i) 
	{ 
		return (p[i] == i) ? i : 
		(p[i] = findSet(p[i])); 
	}
	bool isSameSet(int i, int j) 
	{ 
		return findSet(i) == findSet(j); 
	}
	void unionSet(int i, int j) 
	{
		if (!isSameSet(i, j)) 
		{ // if from different set
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) 
			p[y] = x; // rank keeps the tree short
			else 
			{ 
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++; 
			}	
		}	
    }	
};

int main() {
    int tc; 
    scanf("%d",&tc);
    repp(t,1,tc) {
        int n,m;
        scanf("%d %d",&n,&m);
        vi bal(n+2,0);
        vi total(n+2,0);
        UnionFind uf(n+2);
        repp(x,1,n) {
            scanf("%d",&bal[x-1]);
        }
        repp(x,1,m) {
            int a,b;
            scanf("%d %d",&a,&b);
            uf.unionSet(a,b);
        }
        repp(x,0,n-1) {
            int parent = uf.findSet(x);
            // printf("parent of %d is %d, val is%d\n",x,parent,bal[x]);
            total[parent] += bal[x];
        }
        bool cek=true;
        repp(x,0,n-1) {
            if (total[x]!=0) {
                // printf("fail at %d: %d\n", x, total[x]);
                cek=false;
                break;
            }
        }
        if(cek) {
            printf("POSSIBLE\n"); 
        }else {
            printf("IMPOSSIBLE\n");
        }
    }
	return 0;
}
/*
2
5 3
100
-75
-25
-42
42
0 1
1 2
3 4
4 2
15
20
-10
-25
0 2
1 3

*/