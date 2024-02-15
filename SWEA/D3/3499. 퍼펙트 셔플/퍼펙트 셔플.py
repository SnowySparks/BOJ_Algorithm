T = int(input())
for tc in range(1, T+1):
    n = int(input())
    lst = input().rstrip().split()
    if n%2 : lst.append('0')
    ans = []
    for i in range((n+1)//2):
        ans.append(lst[i])
        ans.append(lst[i + (n+1)//2])
    if n%2:
        ans.pop()
    
    print(f'#{tc}', *ans)