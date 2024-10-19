#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e15; // 1,000,000,000,000,000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Knapsack 1
    ll n, W; cin >> n >> W;
    vector<ll> w(n), v(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> v[i];
    }
    vector<vector<ll>> dp(n+1, vector<ll>(W+1,0));

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= W; ++j) {
            ll imax;
            if (j-w[i] >= 0) {
                imax = max( v[i] + dp[i][j-w[i]] , dp[i][j] );  
            }
            else 
                imax = dp[i][j];
            dp[i+1][j] = imax;   
        }
    }

    return 0;
}