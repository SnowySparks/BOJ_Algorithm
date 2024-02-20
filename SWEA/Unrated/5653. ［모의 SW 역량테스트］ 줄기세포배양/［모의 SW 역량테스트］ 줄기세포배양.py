from collections import deque
# import sys
# sys.stdin = open('input.txt','r')

mv = [(1, 0), (-1, 0), (0, 1), (0, -1)]

T = int(input())
for tc in range(1, T+1):
    n, m, k = map(int,input().split())
    BASE = max(n,m) + k//2 + 10 
    MAX_LoC = 2*BASE+10
    lst = [ [0] * (MAX_LoC) for _ in range((MAX_LoC))]
    
    
    temp_cell = [] #tuple입력, 입력순서는 생명력, 생성한 시간대, 행위치, 열위치
    for r in range(BASE, BASE+n):
        lst[r][BASE:BASE+n] = list(map(int,input().split()))
        for c in range(BASE, BASE+m):
            if lst[r][c]:
                temp_cell.append((lst[r][c], 0, r, c))
    
    temp_cell.sort(key = lambda x : -x[0])
    # print(temp_cell)
    dq = deque(temp_cell)
    time = 0
    
    while time < k:
        query = len(dq)
        for _ in range(query):
            life, appearTime, r, c = dq.popleft()
            
            if appearTime + life > time:
                dq.append((life, appearTime, r, c))
                continue
            elif appearTime + 2* life > time:
                for dr, dc in mv:
                    nr , nc = r + dr, c + dc
                    if nr < 0 or nc < 0 or nr >= MAX_LoC or nc >= MAX_LoC:
                        continue
                    elif lst[nr][nc] == 0:
                        lst[nr][nc] = life
                        dq.append((life, time+1, nr, nc))
                    else:
                        continue
                if appearTime + 2* life -2 >= time:
                    dq.append((life, appearTime, r, c))
                continue
            else:
                continue
        time+=1
    
    print(f'#{tc} {len(dq)}')
        