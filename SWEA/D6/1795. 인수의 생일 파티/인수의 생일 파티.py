from heapq import heappop, heappush
INF = 10**9
heap = []

def dijkstra(gh ,start : int = 0) -> int:
    d = [INF] * (N+1)
    d[start] = 0
    heappush(heap, (0, start))
    
    while heap:
        dist, loc = heappop(heap)
        dist = dist
        
        if d[loc] < dist:
            continue
        
        for cost, nxt in gh[loc]:
            new_dist = dist + cost
            if new_dist < d[nxt]:
                d[nxt] = new_dist
                heappush(heap, (new_dist, nxt))
    
    return d

T = int(input())
for tc in range(1, T+1):
    N, M, X= map(int,input().split())
    gh_forward = [ [] for _ in range(N+1)]
    gh_reverse = [ [] for _ in range(N+1)]
    
    for _ in range(M):
        x, y, c = map(int,input().split())
        gh_forward[x].append((c, y))
        gh_reverse[y].append((c, x))
    
    ans = 0
    d1 = dijkstra(gh_forward, X)
    d2 = dijkstra(gh_reverse, X)
    
    for idx in range(1, N+1):
        if idx == X: continue
        ans = max(ans, d1[idx] + d2[idx])
    print(f'#{tc} {ans}')