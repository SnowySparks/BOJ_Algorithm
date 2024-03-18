import sys
def input():
    return sys.stdin.readline().rstrip()

#누적 가중치 설정
WOMAN = 1
MAN = -1

N = int(input())
lst = []
for _ in range(N):
    gender, x = map(int,input().split())
    lst.append((x, WOMAN if gender == 1 else MAN))
#좌표 정렬
lst.sort()

#남여에 대한 가중치 합
psum = 0 
dt = {}
ans = 0
for idx in range(N):
    x, gender_weight = lst[idx]
    psum += gender_weight
    
    #처음 나오는 값 -> 현재 인덱스를 넣음
    if psum not in dt:
        dt[psum] = idx
        
    #아닌경우 : 현재 위치 - (현 psum이 처음 등장한 좌표 "바로 다음의" 좌표)
    else:
        ans = max(ans, x - lst[ dt[psum] + 1 ][0])
        
    #0인 경우 특수 고려
    if psum == 0:
        ans = max(ans, x - lst[0][0])
print(ans)
