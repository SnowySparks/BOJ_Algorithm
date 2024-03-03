from collections import deque

#방향상수
DOWN = 0
RIGHT = 1
LEFT = 2
UP = 3

mv = [(1, 0), (0, 1), (0, -1), (-1, 0)] # DOWN, RIGHT, LEFT, UP
# p.s. 3 - 방향 = 반대방향

def char_cmd(ch : str) -> int:
    if ch == '<': return LEFT
    elif ch == '>': return RIGHT
    elif ch == '^': return UP
    elif ch == 'v': return DOWN
    elif ch == '.': return -1
    elif ch == '_': return 4
    elif ch == '|': return 5
    elif ch == '?': return 6
    elif ch == '@': return 9
    elif ch == '+': return 7
    elif ch == '-': return 8
    else: return ord(ch) - ord('0') + 10


T = int(input())
for tc in range(1, T+1):
    R, C = map(int,input().split())
    cmd_map = [ input().rstrip() for _ in range(R) ]
    
    isend= False
    for inp in cmd_map:
        if '@' in inp:
            isend = True
            break
    if not isend: #종료 입력 자체가 없으면 어차피 절대 안끝남 -> 조기종료
        print(f'#{tc} NO')
        continue
    
    # v[행][열][메모리값][방향], 방향은 여기서 해당 블럭에 들어오는 방향으로 잡음
    v = [ [ [ [False] * 4 for _ in range(16) ] for _ in range(C) ] for _ in range(R) ]
    dq = deque()
    dq.append(tuple([0, 0, 0, RIGHT]))
    finish = False #도착했다는 의미
    
    #먼저 해당 명령어를 실행하고, 다음 방향으로 이동하는 방식
    while dq:
        r, c, memo, dir = dq.popleft()
        cmd = char_cmd(cmd_map[r][c])
        
        if cmd == 9: #도착도달. 종료
            finish = True
            break
        
        elif cmd == 6:  # ?처리
            for idx in range(4):
                #다음이동, 맵 범위 넘어가면 반대편으로 넘어가는것 고려
                nr = (r + mv[idx][0] + R)%R
                nc = (c + mv[idx][1] + C)%C
                
                if not v[nr][nc][memo][3-idx]:
                    v[nr][nc][memo][3-idx] = True
                    dq.append((nr, nc, memo, idx))
        else:
            #그 외 명령어들. 단 1개의 dq push처리되는 것
            
            #방향돌리기
            if cmd <= 3:
                if cmd >= 0: dir = cmd

            elif cmd == 4: #_
                dir = RIGHT if memo == 0 else LEFT
            elif cmd == 5: #|
                dir = DOWN if memo == 0 else UP
            elif cmd == 7: #+
                memo = (memo + 1)%16
            elif cmd == 8: #-
                memo = (memo + 15) % 16
            else: #수 입력
                memo = cmd - 10
            
            nr = (r + mv[dir][0] + R)%R
            nc = (c + mv[dir][1] + C)%C
            
            if not v[nr][nc][memo][3-dir]:
                v[nr][nc][memo][3-dir] = True
                dq.append((nr, nc, memo, dir))
    
    print(f'#{tc} {"YES" if finish else "NO"}')