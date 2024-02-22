T = 10
N = 1
S = 2
for tc in range(1, T + 1):
    n = int(input())  # always 100
    lst = [list(map(int, input().split())) for _ in range(n)]
    ans = 0
    for c in range(n):
        check_red = False
        for r in range(n):
            if lst[r][c] == N:
                check_red = True
            elif lst[r][c] == S and check_red:
                ans += 1
                check_red = False
    print(f'#{tc} {ans}')

# 원리 :
# 어차피 위에서 (0) 부터 아래로 (100) 까지 가면서 어차피
# N 과 S가 서로 만나면 되는 구조이니
# 위에서 탐색하면서 N이 탐색하면 플래그 달고
# S가 탐색되고 플래그가 달려 있으면 그때 답이 카운팅 되는 방식
