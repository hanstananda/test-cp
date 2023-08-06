#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

using namespace std; 


vector<int> ships;
int memo[200][101001];
bool leftSide[200][101001];
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
        lim *= 1000;
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
            ships.push_back(in);
        } while (1);
        int n = ships.size();
        // process
        memset(memo,-1,sizeof(memo));
        memset(leftSide,0,sizeof(leftSide));
        int ans = dp(0, lim, lim);
        // printf("%d\n", ans);
        cout<<ans<<"\n";        
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