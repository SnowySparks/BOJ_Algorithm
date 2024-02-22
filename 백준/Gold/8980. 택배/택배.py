import sys
# sys.stdin = open('input.txt','r')
def input():
    return sys.stdin.readline().rstrip()
n, c = map(int,input().split())
m = int(input())

lst = [0] * (n + 1) #해당 마을에서 실질적으로 받은 박스 총 갯수
send_lst = [] #m개의 send목록
for _ in range(m):
    send_lst.append(tuple(map(int,input().split())))
    
#받은마을 오름차순, 동일하면 보낸마을 내림차순
send_lst.sort(key = lambda x : (x[1], -x[0]))

for idx in range(m):
    #보낸 마을, #받는 마을, 보내야 할 박스 양
    send, receive, box = send_lst[idx] 
    
    #현재 마을에 받을 수 있는 박스 총양
    #어차피 트럭이 최대 용량에 의해 자동적으로 c가 최대임이 보장
    available = c
    
    #해당 명령을 시행하는 경우 send 부터 receive-1 마을까지의 택배에 영향을 끼칠 수 밖에 없음
    #따라서 해당 구간에 실질적으로 보낸 박스만큼 이용 가능양에서차감해야함
    for check_village in range(send+1,receive):
        available = max(0, available - lst[check_village])
        
    #이용 가능한 박스 혹은 보내야 할 박스 중 최소값을 
    #현재 이 마을에 받을 박스 양에 가산함
    lst[receive] += min(available, box)

print(sum(lst))