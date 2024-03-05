import sys
from collections import defaultdict
def input():
    return sys.stdin.readline().rstrip()

def dfs(root : str) -> int:
    res = 0
    for child in data[root]:
        if child in data:
            if not v[child]: 
                v[child] = True
                res += dfs(child)
        else:
            if not v[child]:
                v[child] = True
                res+=1
    return res

while True:
    n = int(input())
    if n == 0:
        break
    root = ''
    data = defaultdict(list)
    v = defaultdict(bool)
    for idx in range(n):
        key, lst = input().split(':')
        if idx == 0: root = key
        data[key].extend(lst.rstrip('.').split(','))
    v[root] = True
    print(dfs(root))