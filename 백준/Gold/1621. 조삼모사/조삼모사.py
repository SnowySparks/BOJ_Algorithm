N = int(input())
K, C = map(int,input().split())
lst = list(map(int,input().split()))
dp = [0]*(N+2)
nt = [0]*(N+2)
for i in range(N-1,-1,-1):
    dp[i] = dp[i+1] + lst[i]
    if i < N-K+2 and dp[i] > dp[i+K]+C:
        dp[i] = dp[i+K]+C
        nt[i]=1
print(dp[0])
loc = 0
st = []

while(loc < N) :
    if nt[loc]==1:
        st.append(loc+1)
        loc+=K
    else: loc+=1
    
print(len(st))
for i in st : print(i)