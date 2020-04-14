//20
vector<int> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(long long int i = 3; i*i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i <= limit)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}