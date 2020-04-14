//11
int BestSumContiguosSubarray(vector<int> arr)
{
    int best = 0, sum = 0, n = arr.size();
    for(int k = 0; k < n; k++)
    {
        sum = max(arr[k], sum + arr[k]);
        best = max(best,sum);
    }
    return best;
}

