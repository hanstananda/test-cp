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


int baseCost = 60;
int cost(int pos) {
    return baseCost+pos-'A'+1;
}

int main() {
    string in;
    // setup
    vi sources[200];
    vi dest[200];
    set<char> letters;
    set<char> candidates;
    set<char> completed; 
    set<char> todo;

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
        todo.insert(dst);
        todo.insert(src);
    }

    
    for(auto i:letters) {
        // cout<<"Checking "<<i<<"\n";
        if (sources[i].size()==0) {
            cout<<"Starting with "<<i<<"\n";
            candidates.insert(i);
        }
    }

    vector<int> workers(5,0);
    vector<char> work(5,0);
    int curTime=0;
    while(completed.size()!=letters.size()) {
        cout<<"Curtime: "<<curTime<<"\n";
        for(int i=0;i<workers.size();i++) {
            workers[i]=max(workers[i]-1,0); // do 1 step 
            if(workers[i]==0) {
                // check if any work is done by this worker, add it to completed 
                if(work[i]!=0) {
                    completed.insert(work[i]);
                    cout<<"Completed "<<work[i]<<" at "<<curTime<<"\n";
                    work[i]=0;
                }
                if (!candidates.empty()) {
                    // add candidate to workers
                    char assignee=*candidates.begin(); // set is automatically sorted alphabetically, get first item 
                    workers[i]=cost(assignee);
                    todo.erase(assignee);
                    candidates.erase(assignee);
                    work[i]=assignee;
                    cout<<"inserting "<<assignee<<" to worker "<<i<<" for "<<cost(assignee)<<"\n";
                }
            }
        }

        // add all possible candidates 
        for(auto i:todo) {
            bool safe=1;
            for(auto j:sources[i]) {
                if(completed.count(j)==0) {
                    safe=0;
                    break;
                } 
            }
            if(safe) { // add this to todo and assign later
                candidates.insert(i);
            }
        }

        for(int i=0;i<workers.size();i++) {
            if(workers[i]==0) {
                if (!candidates.empty()) {
                    // add candidate to workers
                    char assignee=*candidates.begin(); // set is automatically sorted alphabetically, get first item 
                    workers[i]=cost(assignee);
                    todo.erase(assignee);
                    candidates.erase(assignee);
                    work[i]=assignee;
                    cout<<"inserting "<<assignee<<" to worker "<<i<<" for "<<cost(assignee)<<"\n";
                }
            }
        }
        curTime+=1;
    }
    cout<<curTime-1<<"\n";
	return 0;
}
