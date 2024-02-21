import sys
from collections import deque
n = int(input())
lst = list(map(int,sys.stdin.readline().rstrip().split()))
dq = deque()

val = 1
for idx in range(n-1,-1,-1):
    if lst[idx] == 1:
        dq.appendleft(val)
    elif lst[idx] == 2:
        temp = dq.popleft()
        dq.appendleft(val)
        dq.appendleft(temp)
    else:
        dq.append(val)
    val+=1
    
print(*list(dq))