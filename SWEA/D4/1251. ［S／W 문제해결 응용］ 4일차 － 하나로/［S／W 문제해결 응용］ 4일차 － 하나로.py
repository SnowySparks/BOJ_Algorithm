from heapq import heappop, heappush
from math import floor
def dist(a: int, b : int) ->float:
    return E*((X[a] - X[b])**2 + (Y[a] - Y[b])**2)

heap = []
T = int(input())
for tc in range(1, T+1):
    n = int(input())
    p = list(range(n))
    X = list(map(int, input().split()))
    Y = list(map(int, input().split()))
    E = float(input())

    v = [False] * n
    heap.clear()
    v[0] = True
    ans = 0
    
    for idx in range(1, n):
        heappush(heap, (dist(0, idx), idx))
    
    connected = 0
    while heap and connected < n-1:
        cost, nxt = heappop(heap)
    
        if v[nxt]:
            continue
        
        v[nxt] = True
        connected += 1
        ans += cost
        
        for idx in range(n):
            if v[idx]: continue
            heappush(heap, (dist(nxt,idx), idx))
            
    print(f'#{tc} {floor(ans + 0.5)}')
