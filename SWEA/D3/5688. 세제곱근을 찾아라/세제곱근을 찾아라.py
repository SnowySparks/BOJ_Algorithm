T = int(input())
for tc in range(1, T+1):
    N = int(input())
    x = -1
    if round(N**(1/3))**3 == N:
        x = round(N**(1/3))
    print(f'#{tc} {x}')