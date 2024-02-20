T = int(input())
for tc in range(1, T+1):
    N = int(input())
    farm = [[price for price in map(int, input())] for _ in range(N)]
    up_farm = farm[:N//2]
    down_farm = farm[N//2+1:]
    middle = farm[N//2]
    cnt = 1
    harvest = 0

    for i in range(0, N//2):
        start = N//2-i
        harvest += sum(up_farm[i][start:start+cnt])
        harvest += sum(down_farm[-(i+1)][start:start+cnt])
        cnt += 2
    harvest += sum(middle)
    print(f'#{tc} {harvest}')