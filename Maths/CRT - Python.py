def gcdExtended(a, b):
    if a == 0 :
        return b,0,1
             
    gcd,x1,y1 = gcdExtended(b%a, a)
    x = y1 - (b//a) * x1
    y = x1
    return gcd,x,y

def solve_crt_2(a_0, n_0, a_1, n_1):
    g, x, y = gcdExtended(n_0, n_1)
    if (a_1 - a_0) % g:
        return -1, -1
    
    k_0 = x * (a_1 - a_0) // g
    lcm = n_0 // g * n_1
    ans = k_0 * n_0 + a_0

    ans %= lcm
    if ans < 0:
        ans += lcm

    return ans, lcm

def crt(a, m):
    x = a[0]
    mod = m[0]

    for i in range(1, len(a)):
        x, mod = solve_crt_2(x, mod, a[i], m[i])
        if x == -1:
            return -1, -1
        
    return x, mod
