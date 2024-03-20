from math import floor
INF = 10**9 * 1.0
FIX = 10**7
def tsp(loc, state):
    if loc == n:
        return 1.0
    if dp[state] != -1:
        return dp[state]
    dp[state] = -INF
    for idx in range(n):
        if state & (1<<idx): continue
        dp[state] = max(dp[state], tsp(loc + 1, state | (1 << idx)) * (lst[loc][idx]/100))
    return dp[state]
 
 
T = int(input())
for tc in range(1, T+1):
    n = int(input())
    lst = [ list(map(int, input().split())) for _ in range(n)]
    dp = [-1] * (1 << n)
    res = tsp(0, 0) * 100
    # res = floor(res*FIX + 0.5)/FIX
    print(f'#{tc} {res:.06f}')