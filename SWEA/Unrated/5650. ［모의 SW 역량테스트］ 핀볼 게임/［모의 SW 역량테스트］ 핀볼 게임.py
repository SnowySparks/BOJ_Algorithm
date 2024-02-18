# import sys
# sys.stdin = open('input.txt','r')

DOWN = 0
LEFT = 1
UP = 2
RIGHT = 3
REFLECT = -1

mv = [(1, 0), (0, -1), (-1, 0), (0, 1)]

block = [
    [0, 1, 2, 3],
    [RIGHT, UP, REFLECT, REFLECT],
    [REFLECT, DOWN, RIGHT, REFLECT],
    [REFLECT, REFLECT, LEFT, DOWN],
    [LEFT, REFLECT, REFLECT, UP],
    [REFLECT, REFLECT, REFLECT, REFLECT]
]

wp = [[] for _ in range(11)]

def bfs(cr, cc) -> int:
    res = 0
    for i in range(4):
        dir = i
        cnt = 0
        nr , nc  = cr, cc
        while True:
            dr, dc = mv[dir]
            nr, nc = nr + dr, nc + dc
            
            #밖으로 나간 경우 및 REFLECT
            if nr < 0 or nc < 0 or nr >=n or nc >=n or (1<=gh[nr][nc]<=5 and block[gh[nr][nc]][dir] == REFLECT):
                res = max(res, 2*cnt + 1)
                break
            #블랙홀 혹은 자기자신 위치
            elif gh[nr][nc] == -1 or (nr == cr and nc == cc):
                res = max(res, cnt)
                break
            #조기종료조건 - 최적화
            elif gh[nr][nc] == 0 and cnt == 0:
                break
            #웜홀
            elif gh[nr][nc] >=6:
                wpidx = gh[nr][nc]
                if wp[wpidx][0] == (nr, nc,):
                    nr, nc = wp[wpidx][1]
                else:
                    nr, nc = wp[wpidx][0]
            elif gh[nr][nc] > 0:
                cnt+=1
                dir = block[gh[nr][nc]][dir]
            else: continue
    return res

T = int(input())
for tc in range(1, T+1):
    n = int(input())
    gh = [ list(map(int,input().split())) for _ in range(n)]
    wp = [[] for _ in range(11)]
    wpcnt = [0]*11
    ans = 0
    for r in range(n):
        for c in range(n):
            if gh[r][c] >= 6:
                wp[gh[r][c]].append((r, c,))
    
    for r in range(n):
        for c in range(n):
            if gh[r][c] == 0:
                ans = max(ans, bfs(r, c))
    print(f'#{tc} {ans}')