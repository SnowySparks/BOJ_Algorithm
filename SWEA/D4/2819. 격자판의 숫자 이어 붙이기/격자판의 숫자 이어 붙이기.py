num_lst = set()

mv = [(1, 0), (-1, 0), (0, 1), (0, -1)]

def dfs(r : int, c : int, cnt : int ,psum :int = 0)-> None:
    if cnt == 7:
        num_lst.add(psum)
        return
    
    for dr, dc in mv:
        nr, nc = r + dr, c + dc
        if nr < 0 or nc < 0 or nr >= 4 or nc >= 4:
            continue
        dfs(nr, nc, cnt+1, psum*10 + lst[nr][nc])

T = int(input())
for tc in range(1, T+1):
    lst = [list(map(int,input().split())) for _ in range(4)]
    for r in range(4):
        for c in range(4):
            dfs(r, c, 1 ,lst[r][c])
    print(f'#{tc} {len(num_lst)}')
    num_lst.clear()