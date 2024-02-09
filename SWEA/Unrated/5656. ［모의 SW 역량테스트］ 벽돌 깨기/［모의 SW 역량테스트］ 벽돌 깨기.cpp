from collections import deque
from copy import deepcopy
ans = 0
def left_block(lst) -> int:
    #입력받은 남은 블럭들의 개수 카운팅
    cnt = 0
    for row in range(H):
        for col in range(W):
            if lst[row][col] : cnt+=1
    return cnt

def move_blocks(lst) :
    # lst에 담긴 블럭들을 전부 이동
    # deque를 이용(혹은 스택) 통해 쉽게 전부 아래로 이동 가능
    dq = deque()
    for col in range(W):
        for row in range(H):
            if lst[row][col]:
                dq.append(lst[row][col])
                lst[row][col] = 0
        for row in range(H-1,-1,-1):
            if not dq: break
            lst[row][col] = dq.pop()

def delete_block(loc : int, lst : list) :
    #loc 열에 공을 떨굴 경우의 시물레이션 함수
    sr = 0 #처음 블록이 있는 위치 탐색
    for r in range(H):
        if lst[r][loc]:
            sr = r
            break
    #bfs simulation
    #tuple형태로 주입: 행, 열, 범위
    dq = deque()
    dq.append((sr, loc, lst[sr][loc],))
    while dq:
        r, c, d = dq.popleft()
        d-=1
        lst[r][c]=0
        
        for row in range(max(r-d, 0), min(r + d, H-1) + 1):
            if lst[row][c]:
                dq.append((row, c, lst[row][c]))
                lst[row][c] = 0
        for col in range(max(c-d, 0), min(c + d, W-1) + 1):
            if lst[r][col]:
                dq.append((r, col, lst[r][col]))
                lst[r][col] = 0
    move_blocks(lst)
    
def dfs(cnt : int, lst : list):
    global ans
    #모든 공 투척에 대한 경우들 백트래킹
    #cnt : 공 투척 횟수
    #lst : 현재 입력받은 리스트 정보. 
    if cnt == N:
        ans = min(ans, left_block(lst))
        return
    
    #조기종료 -> 블록이 하나도 없는경우. 가장 맨 바닥만 탐색
    zero = True
    for col in range(W):
        if lst[H-1][col]:
            zero = False
            break
    if zero:
        ans = 0
        return
    
    #백트래킹용 백업용 리스트
    backup = deepcopy(lst)
    
    #공을 쏘는데 있어서 빈 공간을 쏠 필요 없음
    for col in range(0, W):
        if (lst[H-1][col] == 0): continue    
        delete_block(col, lst)
        dfs(cnt+1, lst)
        lst = deepcopy(backup)


T = int(input())
for tc in range(1, T+1):
    #input
    N, W, H = map(int,input().split()) #공 호출수, 너비(열), 높이(행)
    lst = [list(map(int,input().split())) for _ in range(H)]
    ans = left_block(lst) #초기설정
    dfs(0, lst)
    print(f'#{tc} {ans}')