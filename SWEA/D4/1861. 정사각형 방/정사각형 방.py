MAX_VAL = 10**9
mv = [(-1, 0), (1, 0), (0, 1), (0, -1)]

def dfs(r, c):
    if dp[r][c] != -1:
        return dp[r][c]
    
    res = 1
    for dr, dc in mv:
        nr, nc = r + dr, c + dc
        if nr < 0 or nr >= n or nc < 0 or nc >= n:
            continue
        if lst[nr][nc] == lst[r][c] + 1:
            res = max(res, dfs(nr, nc) + 1)
    dp[r][c] = res
    return dp[r][c]

T = int(input())
for tc in range(1, T + 1):
    n = int(input())
    lst = [ list(map(int,input().split())) for _ in range(n)]
    dp = [ [-1] * n for _ in range(n)]
    
    ans = -1
    room_val = 0
    
    for r in range(n):
        for c in range(n):
            res = dfs(r, c)
            if ans < res or ans == res and room_val > lst[r][c]:
                ans = res
                room_val = lst[r][c]

    print(f'#{tc} {room_val} {ans}')