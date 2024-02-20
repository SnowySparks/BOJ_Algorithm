from collections import deque
# import sys
# sys.stdin = open('input.txt','r')

mv = [(0, 1), (0, -1), (-1, 0), (1, 0)]

T = int(input())
for tc in range(1, T+1):
    max_outline = 0
    n = int(input())
    dq = deque()
    for _ in range(n):
        r, c, dir, power = map(int,input().split())
        r*=2; c*=2
        max_outline = abs(max(abs(r), abs(c), max_outline))
        dq.append(tuple([r, c, dir, power]))
    ans = 0
    while dq:
        q = len(dq)
        loc = {}
        for _ in range(q):
            r, c, dir, power = dq.popleft()
            r += mv[dir][0]
            c += mv[dir][1]
            
            if abs(r) > max_outline or abs(c) > max_outline:
                continue
            
            if not (r, c) in loc:
                loc[(r, c,)] = []
            loc[(r, c,)].append((dir, power,))
        
        for k in loc:
            if len(loc[k]) == 1:
                dq.append( (k[0], k[1], loc[k][0][0], loc[k][0][1]))
            else:
                for p in loc[k]:
                    ans+=p[1]
    print(f'#{tc} {ans}')