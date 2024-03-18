T = int(input())
for tc in range(1, T+1):
    lst = list(map(int,input().split()))
    ans = 0
    for idx in range(len(lst)-1, 0, -1):
        if lst[idx] > lst[idx -1]:
            continue
        else:
            diff = lst[idx-1] - lst[idx] + 1
            if lst[idx-1] - diff <= 0:
                ans = -1
                break
            else:
                lst[idx-1] -= diff
                ans += diff
    print(f'#{tc} {ans}')