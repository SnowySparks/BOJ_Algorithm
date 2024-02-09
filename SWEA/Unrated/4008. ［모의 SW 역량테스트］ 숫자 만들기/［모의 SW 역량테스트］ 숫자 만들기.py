
def dfs(total, cnt) -> None:
    global ans_max
    global ans_min
    # params
    # total : 현재 연산의 총합
    # cnt : 총 연산횟수
    if cnt == N-1:
        ans_max = max(ans_max, total)
        ans_min = min(ans_min, total)
        return
    else:
        if oper[0]:
            oper[0]-=1
            dfs(total + arr[cnt+1], cnt+1)
            oper[0]+=1
        
        if oper[1]:
            oper[1]-=1
            dfs(total - arr[cnt+1], cnt+1)
            oper[1]+=1
        
        if oper[2]:
            oper[2]-=1
            dfs(total * arr[cnt+1], cnt+1)
            oper[2]+=1
        
        if oper[3]:
            oper[3]-=1
            dfs(int(total / arr[cnt+1]), cnt+1)
            oper[3]+=1
    return
    

T = int(input())
for tc in range(1, T+1):
    # input
    N = int(input())
    oper = list(map(int,input().split()))
    arr = list(map(int,input().split()))
    
    # 초기화
    ans_max = - 10**9 - 100
    ans_min = -ans_max
    
    # 백트래킹 실행
    dfs(arr[0], 0)
    
    print(f'#{tc} {ans_max - ans_min}')
    