from collections import deque
T = int(input())
for tc in range(1, T+1):
    N, K = map(int,input().split())
    mr = N//4 #최대 회전 수 +1, 동시에 비밀번호 길이
    answer_set = set()
    s = input() #문자열 입력 - 중복값 제거
    answer_set.add(s[:mr])
    answer_set.add(s[mr:mr*2])
    answer_set.add(s[mr*2:mr*3])
    answer_set.add(s[mr*3:mr*4])

    dq = deque(s)
    for _ in range(1, mr):
        dq.rotate() #1회 회전
        s = ''.join(list(dq))
        answer_set.add(s[:mr])
        answer_set.add(s[mr:mr*2])
        answer_set.add(s[mr*2:mr*3])
        answer_set.add(s[mr*3:mr*4])
    
    lst = sorted(list(answer_set),reverse=True)
    print(f'#{tc} {int(lst[K-1],16)}')