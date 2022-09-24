//20
vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}

//12
vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}

//11
vector<int> Phi;
void phiSieve(int n)
{
	Phi.resize(n + 1);
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

//35
vector<lli> sieveMulFunction(lli n)
{
    vector<lli> primes, lp(n+1), f(n+1), cnt(n+1), pot(n+1);
    f[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}


// Segmented Sieve
const lli L1D_CACHE_SIZE = 32768;
vector<lli> primes;

void segmented_sieve(lli limit)
{
    if(limit < 2) return; 

    primes.push_back(2);
    lli sqrt_n = sqrt(limit);
    lli segment_size = max(sqrt_n, L1D_CACHE_SIZE);

    vector<char> sieve(segment_size), is_prime(sqrt_n + 1, true);
    vector<lli> primes_segment, multiples;

    lli i = 3, n = 3;

    for (lli low = 0; low <= limit; low += segment_size)
    {
        fill(all(sieve), true);

        lli high = min(low + segment_size - 1, limit);

        for (; i * i <= high; i += 2)
            if (is_prime[i])
            {
                primes_segment.push_back(i);
                multiples.push_back(i*i-low);
                for (lli j = i * i; j <= sqrt_n; j += i)
                    is_prime[j] = false;
            }

        for (int i = 0; i < SZ(primes_segment); i++)
        {
            for (lli &j = multiples[i]; j < segment_size; j += 2*primes_segment[i])
                sieve[j] = false;
            multiples[i] -= segment_size;
        }   

        for (; n <= high; n += 2)
            if (sieve[n - low]) // n is a prime
                primes.push_back(n);                
    }
}