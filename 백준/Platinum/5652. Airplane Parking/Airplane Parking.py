t = int(input().rstrip())

dp = [ [0] * 600 for _ in range(600)]

for _ in range(t):
    n = int(input().rstrip())
    tm = [ tuple(map(int, input().split())) for _ in range(n) ]
    tlst = []
    for a in tm: 
        tlst.append(a[0])
        tlst.append(a[1])
    tlst.sort()
    opt_time = {}
    for a in tlst:
        if opt_time.get(a,-1)==-1: opt_time[a] = len(opt_time)
    for a in tm:
        dp[ opt_time[ a[0]]][ opt_time[ a[1]]] += 1
    
    for end in range(len(opt_time)):
        for start in range(end-1, -1, -1):
            max_v = 0
            for k in range(end-1,start,-1):
                max_v = max(max_v, dp[start][k]+dp[k][end])
            dp[start][end] += max_v
    print(dp[0][len(opt_time)-1])
    for i in range(len(opt_time)):
        for k in range(len(opt_time)):
            dp[i][k] = 0
    tlst.clear()