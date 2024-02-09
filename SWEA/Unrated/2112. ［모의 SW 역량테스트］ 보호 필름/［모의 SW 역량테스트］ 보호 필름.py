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


T = int(input())
for tc in range(1, T+1):
    CHECKED = False
    #input
    D, W, K = map(int,input().split()) #두께, 너비, 연속길이 수
    arr =[ list(map(int,input().split())) for _ in range(D) ]
    change_row = [EMPTY] * D #약품 주입 칸
    
    allcheck()
    
    if (allcheck()): #약품 처리 안하고 성공하면 그 즉시 다음 테스트 케이스로
        print(f'#{tc} 0')
        continue
    
    cnt = 1
    while cnt < K:
        for lst in combinations(range(D), cnt): #순열 도면서 모든 경우의 수 탐색
            #비트마스킹 이용하면서 A, B에 대한 약품처리 모든 경우의 수 탐색
            for i in range( (1<<cnt) ):
                for j in range(cnt):
                    if i & (1<<j) : 
                        change_row[lst[j]] = B
                    else:
                        change_row[lst[j]] = A
                
                if allcheck(): #확인시 그 즉시 종료
                    CHECKED = True
                    break
            if CHECKED:
                break
            #원복
            for val in lst:
                change_row[val] = EMPTY
        if CHECKED:
            break
        cnt += 1
    print(f'#{tc} {cnt}')