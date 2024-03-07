from collections import defaultdict
import sys
def input():
    return sys.stdin.readline().rstrip()

# sys.stdin = open('./누적합/input.txt','r')

MOD = 10**9 + 7 #소수->경우의 수에서 나누기전용
MAX_F = 200001

#n : A배열크기
#m : A배열의 구간입력 횟수 (x, y)x<=y꼴

f = [1] * MAX_F#factorial 
for i in range(1, MAX_F):
    f[i] = f[i-1]*i%MOD

T = int(input())
for _ in range(T):
    n, m = map(int,input().split()) #n, m 입력
    A = [0] + list(map(int,input().split())) #A 배열 입력
    prefix_sum = [0] * (n+2) #누적합 전용, 인덱스 범위 주의
    
    #누적합 입력
    for _ in range(m):
        x, y = map(int,input().split())
        prefix_sum[x]+=1
        prefix_sum[y+1]-=1
    #카운팅. 경우의 수 
    cnt = 1 
    non_zero = 0 #누적합 결과에서 0이 아닌 경우의 수 카운팅
    
    prefix_sum_cnt = defaultdict(int)
    
    #누적합 적용 및, 해당 누적합 결과를 카운팅
    for idx in range(1, n+1):
        prefix_sum[idx] += prefix_sum[idx-1]
        if prefix_sum[idx]:
            prefix_sum_cnt[prefix_sum[idx]]+=1
            non_zero+=1
    
    for val in prefix_sum_cnt.values():
        cnt = cnt * f[val] % MOD
    
    cnt = cnt * f[n - non_zero] %MOD #나머지 0에 대한 순열곱 처리
    
    prefix_sum.sort(key = lambda x : -x) #내림차순 정렬
    A.sort(key = lambda x : -x) #내림차순 정렬
    total = 0
    for idx in range(n):
        if (prefix_sum[idx] <=0): break
        total += prefix_sum[idx]*A[idx]
    
    print(total,cnt)
    
    
    
    