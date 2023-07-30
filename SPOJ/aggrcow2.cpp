#include <cstdio>
#include <algorithm>
#include <vector>
#define ll long long 

using namespace std; 


bool checkPlacement(vector<int> pos, int cow, int dist) {
    int numPlaced=0;
    int nextPos=0;
    for(int i=0;i<pos.size();i++) {
        if(pos[i]>=nextPos) {
            // printf("tes %d \n", pos[i]);
            numPlaced+=1;
            nextPos= pos[i] + dist;
        }
        if (numPlaced >= cow) {
            break; 
        }
    }
    // printf("%d: %d %d\n", dist, numPlaced, nextPos);
    return numPlaced >= cow;
}

int main() {
    int tc;
    scanf("%d",&tc);
    while(tc--) {
        vector<int> pos;
        // scan inputs 
        int n,c; 
        scanf("%d %d",&n, &c);
        int in;
        for(int i=0;i<n;i++) {
            scanf("%d",&in);
            pos.push_back(in);
        }
        // sort possible positions 
        sort(pos.begin(), pos.end());
        int lo = 0; 
        int hi = pos[pos.size()-1];
        int mid;
        int ans = 0; 
        while (lo<=hi)
		{
			mid=(lo+hi)/2;
			if (checkPlacement(pos, c, mid))
            {
                lo=mid+1;
                ans = max(ans,mid);
            } else
            {
                hi=mid-1; 
            }
		}
        printf("%d\n", ans);
    }
    
}