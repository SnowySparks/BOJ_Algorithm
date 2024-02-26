import math

T = int(input())
for tc in range(1, T + 1):
    n = int(input())

    ans = 2*n+1
    y = 1
    while y <= n:
        x = int(math.sqrt(n**2 - y**2))
        ans += (2 + 4*x)
        y+=1
    print(f'#{tc} {ans}')