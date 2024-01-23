import sys
input = sys.stdin.readline
MAX_VAL = 1120
dp = [ [0] * 15 for _ in range(MAX_VAL+1)]
dp[0][0] = 1
primes = []
arr = [0] * (MAX_VAL + 1)

# 소수찾기
for num in range(2,MAX_VAL+1):
    if not arr[num] : primes.append(num)
    for prime in primes :
        if num*prime > MAX_VAL: break
        arr[num*prime] = prime
        if num%prime==0 : break

for prime in primes:
    for num in range(MAX_VAL,1,-1):
        for k in range(1,15):
            if num - prime >= 0:
                dp[num][k] += dp[num-prime][k-1]

t = int(input().rstrip())

for _ in range(t):
    a, b = map(int,input().rstrip().split())
    print(f'{dp[a][b]}')