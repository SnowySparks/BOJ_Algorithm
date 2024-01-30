T = int(input())
for t in range(1,T+1):
    n, k = map(int,input().split())
    lst = [ list(map(int,input().split())) for _ in range(n)]
    ans, cnt = 0, 0
    for row in range(n):
        cnt = 0
        for col in range(n):
            if lst[row][col] :
                cnt+=1
            if lst[row][col]==0 or col == n-1:
                if cnt==k: ans+=1
                if not lst[row][col] : cnt=0
    for col in range(n):
        cnt = 0
        for row in range(n):
            if lst[row][col] :
                cnt+=1
            if lst[row][col]==0 or row == n-1:
                if cnt==k: ans+=1
                if not lst[row][col] : cnt=0
    print(f'#{t} {ans}')
                