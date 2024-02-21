def make_check_lst(omok_lst, row_lst, col_lst, N):
    omok_lst_trans = list(zip(*omok_lst))
    for i in range(N-4):
        for j in range(N-4):
            check = 0
            if omok_lst[i][j] == 'o':
                for k in range(1, 5):
                    if omok_lst[i+k][j+k] == 'o':
                        check += 1
                if check == 4:
                    return True

    for i in range(N-4):
        for j in range(1, N-3):
            check = 0
            if omok_lst[i][-j] == 'o':
                for k in range(1, 5):
                    if omok_lst[i+k][-(j+k)] == 'o':
                        check += 1
                if check == 4:
                    return True

    for row in range(N):
        for col in range(N-4):
            check_row = omok_lst[row][col:col+5]
            check_col = omok_lst_trans[row][col:col+5]
            if check_row.count('o') == 5 or check_col.count('o') == 5:
                return True
    return False

def check_omok(row_lst, col_lst, N):

    for i in range(1, 6):
        if row_lst.count(i) == 5 or col_lst.count(i) == 5:
            return True
    return False


T = int(input())
for tc in range(1, T+1):
    N = int(input())

    omok_input_lst = [list(input()) for _ in range(N)]
    row_stone = []
    col_stone = []
    dig_lst = []

    if make_check_lst(omok_input_lst, row_stone, col_stone, N):
        print(f'#{tc} YES')
    elif check_omok(row_stone, col_stone, N):
        print(f'#{tc} YES')
    else:
        print(f'#{tc} NO')


