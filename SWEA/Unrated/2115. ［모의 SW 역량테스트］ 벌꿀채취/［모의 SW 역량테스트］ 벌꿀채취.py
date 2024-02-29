from itertools import combinations
# import sys
# # sys.stdin = open('input.txt','r')
res = []
a = []
b = []

def calmax(sel_lst : list) -> int:
    max_val = 0
    cal = 0
    for i in range(1, M+1):
        for dt in combinations(sel_lst, i):
            if sum(dt) <= C:
                cal = 0
                for v in dt:
                    cal += v**2
                max_val = max(max_val, cal)
    return max_val
                

def dfs(sr, sc, cnt):
    global ans 
    if cnt == 2:
        for idx in range(res[0][1],res[0][1]+M):
            a.append(lst[res[0][0]][idx])
        
        for idx in range(res[1][1],res[1][1]+M):
            b.append(lst[res[1][0]][idx])
        
            
        ans = max(ans, calmax(a) + calmax(b))
        a.clear()
        b.clear()
        return
    
    for r in range(sr, N):
        if r == sr:
            for c in range(sc, N-M+1):
                res.append((r, c))
                dfs(r, c+M, cnt+1)
                res.pop()
        else:
            for c in range(N-M+1):
                res.append((r, c))
                dfs(r, c+M, cnt+1)
                res.pop()
    return
                 

T = int(input())
for tc in range(1, T + 1):
    N, M, C = map(int,input().split())
    ans = 0
    lst = [ list(map(int,input().split())) for _ in range(N)]
    dfs(0, 0, 0)
    print(f'#{tc} {ans}')
    