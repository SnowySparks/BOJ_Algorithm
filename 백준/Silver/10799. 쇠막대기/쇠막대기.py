import sys

s = sys.stdin.readline().rstrip()
cnt = 0
ans = 0
for idx in range(len(s)):
    if s[idx] == '(':
        cnt+=1
    else:
        cnt-=1
        if s[idx-1]=='(':
            ans+=cnt
        else:
            ans+=1
print(ans)
