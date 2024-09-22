from collections import deque as dq

l = 10**5+1
start, end = map(int,input().split())
visited = [-1] * l

lst = dq()
lst.appendleft(start); visited[start] = 0

while len(lst):
    loc = lst.popleft()
    if loc == end:
        print(visited[loc])
        break
    
    if loc*2 < l and visited[loc*2]==-1:
        lst.appendleft(loc*2)
        visited[loc*2] = visited[loc]
        
        
    if loc - 1 >= 0 and visited[loc-1]==-1:
        lst.append(loc-1)
        visited[loc-1] = visited[loc]+1
    
    if loc + 1 < l and visited[loc+1]==-1:
        lst.append(loc+1)
        visited[loc+1] = visited[loc]+1
    

