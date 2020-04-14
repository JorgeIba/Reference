//15
long computeXOR(int n)
{
    switch( n & 3) // n % 4
    {
        case 0: return n;
        case 1: return 1;
        case 2: return n+1;
        case 3: return 0;
    }
}
long computeXORFromAToB(int a, int b)
{
    return computeXOR(a) ^ computeXOR(b);
}