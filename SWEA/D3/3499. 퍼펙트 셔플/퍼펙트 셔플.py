T = int(input())
for tc in range(1, T + 1):
    N = int(input())
    card_lst = list(input().split())
    if (N % 2) == 1:
        left_lst = card_lst[:N//2+1]
        right_lst = card_lst[N//2+1:]
    else:
        left_lst = card_lst[:N//2]
        right_lst = card_lst[N//2:]
    if (N % 2) == 1:
        right_lst += ['']
    new_card_lst = list(zip(left_lst, right_lst))
    print(f'#{tc} ', end='')
    for new_card in new_card_lst:
        print(*new_card, end=' ')
    print()
