struct RollingHash
{
    lli hash=0, mod, p, magic, inverse_p, size = 0; 
    RollingHash(lli p, lli mod): p(p), mod(mod){ 
        inverse_p = getInverse(); 
        magic = 1;
    }
    void push(char newAdd)
    {
        hash = (hash*p + newAdd*p)%mod;
        magic = (magic*p)%mod;
        //size++;
    }
    void pop(char oldErase)
    {
        hash = (hash - oldErase*magic)%mod;
        if(hash<0) hash += mod;
        magic = (magic*inverse_p)%mod;
    }
    lli getHash(){return hash;}
    lli getInverse()
    {
        lli b = mod - 2; // If mod is prime, p^(mod-2) = 1 (mod m)
        lli res = 1, aux = p;
        while(b) 
        {
            if(b&1) res = (res*aux)%mod;
            b>>=1;
            aux = (aux*aux)%mod;
        }
        return res;
    }
};
