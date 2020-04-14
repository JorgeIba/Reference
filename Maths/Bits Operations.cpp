//10
int lowestBit(int n){ return n&(-n); }
int isOn(int s, int j){  return s & (1 << j); }
int clearBit(int s, int j){ return s & ~(1 << j);  }
int setBit(int s, int j){  return s | (1 << j); }
int toggleBit(int s, int j){  return s ^ (1 << j); }
int isPowerofTwo(int s){ return s & (s-1);   }
int turnOffLastBit(int s){ return s & (s-1);  }
//__builtin_popcount(n) counting the number of 1's
//__builtin_popcountll(n) counting the number of 1's

//13
int getSetBitsFromOneToN(int N)
{ 
    int two = 2,ans = 0; 
    int n = N; 
    while(n){ 
        ans += (N/two)*(two>>1); 
        if((N&(two-1)) > (two>>1)-1) ans += (N&(two-1)) - (two>>1)+1; 
        two <<= 1; 
        n >>= 1; 
    } 
    return ans; 
} 
