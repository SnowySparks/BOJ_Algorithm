from collections import deque
from collections import Counter

T = int(input())
for tc in range(1, T + 1):
    num, k = input().split()
    k = int(k)
    length = len(num)
    same_num = Counter(num).most_common(1)[0][1] >= 2  # 중복되는 숫자 존재하는지 판단
    v = {}  # empty dictionary
    dq = deque()  # BFS 탐색용
    dq.append((num, 0))  # 초기 탐색 입력.
    ans = -1
    while dq:
        now_num, now_swap = dq.popleft()  # 현재 탐색해야 하는 수, 이 수의 "최소 입력"
        if now_swap == k:  # swap 횟수가 K 인경우, 더이상 swap 불가능 
            continue
        lst = list(now_num)  # swap 용이하기 위해 리스트변환, str은 immutable한 문제 때문
        for i in range(length - 1):
            for j in range(i + 1, length):
                lst[i], lst[j] = lst[j], lst[i]  # swap
                a = ''.join(lst) 
                if a not in v:  # 방문 흔적 없으면 방문  및 swap 횟수 등록
                    v[a] = now_swap + 1
                    dq.append((a, now_swap + 1))  # 다음 swap 탐색하기 위해 queue 에 담음
                lst[i], lst[j] = lst[j], lst[i]  # 원복

    for key, val in v.items():
        # 같은 숫자가 존재하거나, 해당 수를 얻는데 있어,  k 에서 최소 swap 수를 뺀 결과가 짝수 인 경우 답 갱신
        if same_num:
            ans = max(ans, int(key))
        elif (k - val) % 2 == 0:
            ans = max(ans, int(key))
    print(f'#{tc} {ans}')