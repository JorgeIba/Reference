//29
void GaussJordanZ2(vector< bitset<maxN> > &equations, vector<int> &ans)
{
	int rows = SZ(equations), cols = maxN;
	for(int i = 0, j = 0; (i < rows) && (j < cols); j++)
	{
		int selected = -1;
		
		for(int k = i; k<rows; k++)
			if(equations[k][j])
				selected = k;
		
		if(selected == -1) continue;
		
		swap(equations[i], equations[selected]);
		swap(ans[i], ans[selected]);

		for(int k = 0; k<rows; k++)
		{
			if(k != i && equations[k][j])
			{
				equations[k] ^= equations[i];
				ans[k] ^= ans[i];
			}
		}
		i++;
	}
}


/*
    If very test case, don't forget
    init basis and sz_basis
    O(d) -> !zeros
    O(d + d) -> zeros
*/
const int LOG_D = 64;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask, bool zeros = false) //Zeros -> make zeros above basis[i]
{
    for(int i = LOG_D-1; i>=0; i--)
    {
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i])
        {
            basis[i] = mask;
			sz_basis++;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++)
			{
				if(j==i) continue;
				if(j < i)
				{
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
				}
				else
				{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
				}
			}
            return;
        }
        mask ^= basis[i];
    }
}