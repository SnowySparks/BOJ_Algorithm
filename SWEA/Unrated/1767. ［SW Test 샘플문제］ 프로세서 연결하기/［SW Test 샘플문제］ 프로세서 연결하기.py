# import sys
# sys.stdin = open('input.txt','r')

T = int(input())
check_core = []
max_core = 0
min_line = 0
mv = [ (1, 0), (-1, 0), (0, 1), (0, -1)]

#상수
CORE = 1
LINE = 2
EMPTY = 0
MAX_LINE = 10**9

#해당 위치 기준으로 (시작점제외) 해당 방향으로 LINE 설치가 가능한가?
def can_connet(r, c, dir):
    dr, dc = mv[dir]
    nr, nc = r + dr, c + dc
    while True:
        if nr < 0 or nr >= N or nc < 0 or nc >= N:
            break
        if lst[nr][nc] != EMPTY:
            return False
        nr += dr
        nc += dc
    return True

#해당 위치 기준으로 (시작점제외) 해당 방향으로 블럭설치 , 기본값 LINE
def set_line(r, c, dir, block = LINE) -> int:
    dr, dc = mv[dir]
    nr, nc = r + dr, c + dc
    cnt = 0
    while True:
        if nr < 0 or nr >= N or nc < 0 or nc >= N:
            break
        lst[nr][nc] = block
        cnt += 1
        nr += dr
        nc += dc
    return cnt
    
#백트래킹
def back_track(cnt, loc, line) -> None:
    global max_core
    global min_line
    # 답 갱신
    if (cnt > max_core):
        max_core = cnt
        min_line = line
    elif cnt == max_core and min_line > line:
        min_line = line
    
    # 종료 조건
    if loc == total_cnt:
        return
    
    #불필요한 탐섹 제거. 연결된 코어 + 남은 탐색 코어수 보다 현재 최대 코어보다 작은 경우 무조건 컷
    #또 같은 경우에 한해서, 현재 탐색된 라인 길이가 갱신된 최소 값보다 크거나 같으면 무시
    if total_cnt - loc + cnt < max_core or total_cnt - loc + cnt == max_core and line >= min_line:
        return
    
    for idx in range(loc, total_cnt):
        for dir in range(4):
            r, c = check_core[idx]
            if can_connet(r, c, dir):
                add_line = set_line(r, c, dir)
                back_track(cnt+1, idx+1, line+add_line)
                set_line(r, c, dir, EMPTY)
    return

for tc in range(1, T+1):
    max_core = 0
    min_line = MAX_LINE
    N = int(input())
    lst = [list(map(int,input().split())) for _ in range(N)]
    check_core.clear()
    for r in range(1, N-1):
        for c in range(1, N-1):
            if lst[r][c] :
                check_core.append((r, c,))
    total_cnt = len(check_core)
    back_track(0, 0, 0)
    
    print(f'#{tc} {min_line}')