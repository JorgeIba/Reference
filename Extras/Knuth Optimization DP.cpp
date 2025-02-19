
// O(N * K)
// opt[i][j-1] <= opt[i][j] <= opt[i-1][j]
// In this case, is opt[i-1][j] <= opt[i][j] <= opt[i][j-1]
// For the way dp is saved
const lli INF = 1e18;
template<class G>
lli knuth_dp(int n, int k, G cost){
    vector< vector<lli> > dp(n+1, vector<lli>(k+1, INF));
    vector< vector<int> > opt(n+1, vector<int>(k+1, n-1));

    // Base cases
    for(int i = 0; i < n; i++){
        dp[i][1] = cost(i, n-1);
        opt[i][1] = n-1;
    }

    // Note we first iterate over cuts
    for(int j = 2; j <= k; j++){
        for(int l = 0; l < n; l++){
            int limit_l = (l ? opt[l-1][j] : 0);
            int limit_r = opt[l][j-1];
            
            for(int r = limit_l; r <= limit_r; r++){
                lli cost_range = cost(l,r) + dp[r+1][j-1];
                if(cost_range < dp[l][j]){
                    dp[l][j] = cost_range;
                    opt[l][j] = r;
                }   
            }
        }
    }
    
    // forr(l, 1, n-1){
    //     forr(j, 2, k) {
    //         if(opt[l][j] == INF) continue; // Valid Cut
    //         assert(opt[l-1][j] <= opt[l][j] && opt[l][j] <= opt[l][j-1]);
    //         // cout << opt[l][j] << " ";
    //     }
    //     // cout << endl;
    // }

    return dp[0][k];
}