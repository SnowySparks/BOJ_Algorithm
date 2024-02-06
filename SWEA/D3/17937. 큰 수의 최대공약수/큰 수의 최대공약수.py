T = int(input())
for tc in range(1,T+1):
    a, b = input().split()
    print(f'#{tc} {a if a==b else 1}')