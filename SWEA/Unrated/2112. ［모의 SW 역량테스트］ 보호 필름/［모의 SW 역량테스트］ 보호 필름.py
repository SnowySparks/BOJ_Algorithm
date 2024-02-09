from itertools import combinations
from collections import deque

# 특성 값들
EMPTY = -1
A = 0
B = 1

#최종 확인 여부용 - global선언 필수
CHECKED = False

def isallow(idx : int) -> bool : #해당 열에서 A 혹은 B 연속적으로 K가 있는가?
    cntA, cntB = 0, 0
    for row in range(D):
        if change_row[row] == EMPTY : #해당 열에 특수처리 안 되어 있을 경우
            if arr[row][idx] == A:
                cntA += 1
                cntB = 0
            else:
                cntA = 0
                cntB += 1
        else: #특수 약품이 처리된 경우
            if change_row[row] == A:
                cntA += 1
                cntB = 0
            else:
                cntA = 0
                cntB += 1
        if cntA >= K or cntB >= K: #적합하면 True 리턴
            return True
    return False #아니면 False 리턴

def allcheck() -> bool: #모든 열에 대해서 체크
    #하나라도 불만족하면 그 즉시 False
    for col in range(W):
        if not isallow(col):
            return False
    return True

def backtracking(idx, cnt, max_val):
    global CHECKED
    if CHECKED : return
    if cnt == max_val:
        if allcheck():
            CHECKED = True
        return
    if CHECKED : return
    for i in range(idx, D):
        change_row[i] = A
        backtracking(i+1, cnt+1, max_val)
        change_row[i] = B
        backtracking(i+1, cnt+1, max_val)
        change_row[i] = EMPTY
    return


T = int(input())
for tc in range(1, T+1):
    #초기화
    CHECKED = False
    #input
    D, W, K = map(int,input().split()) #두께, 너비, 연속길이 수
    arr =[ list(map(int,input().split())) for _ in range(D) ]
    change_row = [EMPTY] * D #약품 주입 칸
    
    if (allcheck()): #약품 처리 안하고 성공하면 그 즉시 다음 테스트 케이스로
        print(f'#{tc} 0')
        continue
    
    ans = 1
    while ans < K:
        backtracking(0, 0, ans)
        if (CHECKED) : break
        ans += 1
    print(f'#{tc} {ans}')