# import sys
# sys.stdin = open('input.txt','r')
#from pprint import pprint as print

mv = [(0, 1), (1, 0), (0, -1), (-1, 0)]
T = int(input())
for t in range(1, T + 1):
    n = int(input())
    lst = [[0]*n for _ in range(n)]
    cnt = 0
    r, c,dir = 0, -1,0
    while cnt < n*n:
        while 1:
            nr, nc = r + mv[dir][0], c+mv[dir][1]
            if nr >= n or nr < 0 or nc >= n or nc < 0  or lst[nr][nc]!=0:
                dir= (dir+1)%4
                break
            cnt+=1
            lst[nr][nc] = cnt
            r, c = nr, nc
    print(f'#{t}')
    for val in lst:
        print(*val)
    