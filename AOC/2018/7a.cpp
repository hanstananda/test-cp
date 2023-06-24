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

int main() {
    string in;
    priority_queue<int> pq;
    // setup
    vi sources[200];
    vi dest[200];
    set<int> letters;
    for(int i=0;i<200;i++) {
        sources[i].clear();
    }

    while(getline(cin, in)) {
        char in1[10], in2[10];
        sscanf(in.c_str(),"Step %s must be finished before step %s can begin.",in1,in2);
        printf("%s %s\n",in1,in2);
        // jsut use ASCII as representation
        int src=in1[0];
        int dst=in2[0];
        sources[dst].pb(src);
        dest[src].pb(dst);

        letters.insert(dst);
        letters.insert(src);
    }

    // get parent and put to pq
    for(auto i:letters) {
        cout<<"Checking "<<i<<"\n";
        if (sources[i].size()==0) {
            cout<<"Starting with "<<i<<"\n";
            pq.push(-i);
        }
    }

    
    vi ans; 
    set<int>completed;
    while(!pq.empty()) {
        int cur = -pq.top();pq.pop();
        if (completed.count(cur)!=0) {
            continue; // counted in already
        }
        ans.pb(cur);
        completed.insert(cur);
        // push all dependents of cur 
        for(auto i:dest[cur]) {
            if(completed.count(i)!=0) { // collected already
                continue;
            }
            // Check if all dependents done 
            bool safe=1;
            for(auto j:sources[i]) {
                if(completed.count(j)==0) {
                    // not yet completed, unsafe to add
                    
                    //char cs=i,cj=j;
                    //cout<<cs<<"is still being blocked by"<<cj<<"\n";
                    
                    safe=0;
                    break;
                } 
            }
            if(safe) {
                pq.push(-i);
            }
        }
    }
    for(auto i:ans) {
        char curans=i;
        cout<<curans;   
    }
    cout<<"\n";
	return 0;
}
