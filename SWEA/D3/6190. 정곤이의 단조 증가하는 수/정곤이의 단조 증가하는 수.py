# 테스트 케이스 T 입력
T = int(input())
for tc in range(1, T+1):
    N = int(input())
    num_lst = list(map(int, input().split()))
    multiply_lst = []
    check_lst = []
    for i in range(len(num_lst) - 1):
        for j in range(i+1, len(num_lst)):
            multiply_lst.append(num_lst[i] * num_lst[j])

    multiply_lst = list(map(str, multiply_lst))
    for mul_num in multiply_lst:
        check = 0
        for i in range(len(mul_num) - 1):
            if int(mul_num[i]) <= int(mul_num[i+1]):
                continue
            else:
                check = 1
                break
        if check:
            continue
        else:
            check_lst.append(int(mul_num))
    if len(check_lst):
        print(f'#{tc} {max(check_lst)}')
    else:
        print(f'#{tc} -1')