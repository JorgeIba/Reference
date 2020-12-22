//29
void GaussJordanZ2(vector< bitset<maxN> > &equations, vector<int> &ans)
{
	int rows = maxN, cols = maxN;
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