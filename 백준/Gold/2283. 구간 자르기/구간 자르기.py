import sys
def input() -> str :
    return sys.stdin.readline().rstrip()

MAX_LOC = 1_000_000
last_loc = 0
n, k = map(int,input().split())

#prefix sum
dp = [0] * (MAX_LOC + 2)
for _ in range(n):
    fr, to = map(int,input().split())
    dp[fr]+=1
    dp[to]-=1
    last_loc = max(last_loc , to)
    
for idx in range(1,last_loc+1):
    dp[idx]+=dp[idx-1]
    
#two pointer
l, r, total, fd = 0, 0, 0, False
while (l <= r and l <= last_loc and r <= last_loc) : 
    if total == k:
        print(l, r)
        fd = True
        break
    
    if total < k:
        total+=dp[r]
        r+=1
    else:
        total-=dp[l]
        l+=1

if not fd:
    print(0, 0)

