from bisect import bisect_left, bisect_right
T = int(input())

ans = 0
def left_sum(idx , total , end):
    global ans
    if idx == end:
        ans += sub_sum.get(K-total,0)
        return
    left_sum(idx+1, total, end)
    left_sum(idx+1, total+lst[idx], end)

def right_sum(idx , total , end):
    if idx == end:
        sub_sum[total] = sub_sum.get(total,0)+1
        return
    right_sum(idx+1, total, end)
    right_sum(idx+1, total+lst[idx], end)

for tc in range(1,T+1):
    N, K = map(int,input().split())
    lst = list(map(int,input().split()))
    sub_sum = {}
    ans = 0
    right_sum(N//2,0,N)
    left_sum(0,0,N//2)
    
    print(f'#{tc} {ans}')
