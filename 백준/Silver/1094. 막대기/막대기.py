n = int(input())
cnt = 0
for i in range(0,7):
    if n & (1<<i):
        cnt+=1
print(cnt)