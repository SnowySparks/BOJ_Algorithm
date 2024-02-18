# import sys
# sys.stdin = open('input.txt','r')

mv = [(0, 0), (-1, 0), (0, 1),(1, 0),(0, -1)]

def isin(r, c, bt : tuple) -> bool:
    return abs(r - bt[1]) + abs(c - bt[0]) <= bt[2]

def BatteryIn(BatteryIdx , lst : list) -> None:
    if lst[0] == -1:
        lst[0] = BatteryIdx
    elif lst[1] == -1:
        lst[1] = BatteryIdx
        if power_result(lst[1]) >= power_result(lst[0]):
            lst[0], lst[1] = lst[1], lst[0]
    else:
        if power_result(BatteryIdx) >= power_result(lst[0]):
            lst[0], lst[1] = BatteryIdx, lst[0]
        elif power_result(BatteryIdx) >= power_result(lst[1]):
            lst[1] = BatteryIdx

def power_result(x : int)->int:
    if x == -1: return 0
    return Battery[x][3]

T = int(input())
for tc in range(1, T+1):
    m, a = map(int,input().split())
    ans = 0
    lstA = [0]
    lstA.extend(map(int,input().split()))
    lstB = [0]
    lstB.extend(map(int,input().split()))
    Battery = []
    for _ in range(a):
        Battery.append(tuple(map(int,input().split()))) #x, y, range, power --> c, r 주의
    ar, ac, br, bc = 1, 1, 10, 10
    for idx in range(m+1):
        ar, ac = ar + mv[lstA[idx]][0], ac + mv[lstA[idx]][1]
        br, bc = br + mv[lstB[idx]][0], bc + mv[lstB[idx]][1]
        aBattery = [-1, -1]
        bBattery = aBattery[:]      
        for i in range(a):
            if isin(ar, ac, Battery[i]):
                BatteryIn(i, aBattery)
            if isin(br, bc, Battery[i]):
                BatteryIn(i, bBattery)
        if aBattery[0] != bBattery[0]:
            ans += power_result(aBattery[0]) + power_result(bBattery[0])
        else:
            ans += max(power_result(aBattery[1]) + power_result(bBattery[0]), power_result(aBattery[0]) + power_result(bBattery[1]))
    print(f'#{tc} {ans}')
    