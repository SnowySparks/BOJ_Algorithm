# import sys
# sys.stdin = open('input.txt','r')

T = int(input())

def isrising(n):
    if n < 10:
        return True
    v = n%10
    while n:
        nv = n%10
        if v < nv:
            return False
        v = min(v, nv)
        n//=10
    return True

for test_case in range(1, T + 1):
    n = int(input())
    lst = list(map(int,input().split()))
    ans = 0
    for i in range(n-1):
        for k in range(i+1,n):
            if isrising(lst[i]*lst[k]):
                ans = max(ans, lst[i]*lst[k])
    print(f'#{test_case} {ans if ans > 0 else -1}')