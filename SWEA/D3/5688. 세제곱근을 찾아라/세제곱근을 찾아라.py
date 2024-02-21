from collections import deque
T = int(input())
for tc in range(1, T+1):
    n = int(input())
    l, r = 1, min(10**6+1, int(  (n+1)**(1/2)))
    ans = -1
    while l <= r:
        mid = (l+r)>>1
        cal = mid**3
        if cal == n:
            ans = mid
            break
        elif cal < n:
            l=mid+1
        else:
            r=mid-1
    print(f'#{tc} {ans}')