def memoized_fibo_aux(t, n):
    if t[n] > 0:
        print "get here once?", t[n]
        return t[n]
    t[n] = memoized_fibo_aux(t, n-1) + memoized_fibo_aux(t, n-2)
    return t[n]

def memoized_fibo(n):
    t = [-1]*(n+1)
    t[0] = t[1] = 1
    r = memoized_fibo_aux(t,n)
    print(t)
    return r,t

r,t = memoized_fibo(9)
print (r,t)
