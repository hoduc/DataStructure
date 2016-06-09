def memoized_cut_rod_aux(p,n,r,s):
    print "n:", n
    if r[n] >= 0:
        print "already in sol:",n, ":",r[n] 
        return r[n]
    if n == 0:
        q = 0
    else:
        q = -1
        oi = -1
        for i in range(1,n+1):
            print "try:", i
            nq = p[i-1] + memoized_cut_rod_aux(p,n-i,r,s)
            print "found (potential) q value:", nq
            #print (n, ":",i,nq)
            if nq > q:
                oi = i
                q = nq
                #s[i] = q
            #q = max(q, p[i-1] + memoized_cut_rod_aux(p, n-i, r,s))
            #else:
               # s[i] = r[
            print "after try:q=", q
        s[n] = oi
    r[n] = q
    print n, "==>", q
    return q

def memoized_cut_rod(p,n):
    r = [-1]*(n+1)
    s = [-1]*(n+1)
    q = memoized_cut_rod_aux(p,n, r, s)
    return (r,s)

def print_memoized_cut_rod_solution(p,n):
    (r,s) = memoized_cut_rod(p,n)
    print r,s
    while n > 0:
        print s[n]
        n -= s[n]

print_memoized_cut_rod_solution([1,5,8,9,10,17,17,20,24,30], 7)
