# import sys
# sys.stdin = open('input.txt','r')
# sys.stdout = open('output.txt','w')

Hex_to_bin = [
    (0, 0, 0, 0), #0
    (0, 0, 0, 1), #1
    (0, 0, 1, 0), #2
    (0, 0, 1, 1), #3
    (0, 1, 0, 0), #4
    (0, 1, 0, 1), #5
    (0, 1, 1, 0), #6
    (0, 1, 1, 1), #7
    (1, 0, 0, 0), #8
    (1, 0, 0, 1), #9
    (1, 0, 1, 0), #A
    (1, 0, 1, 1), #B
    (1, 1, 0, 0), #C
    (1, 1, 0, 1), #D
    (1, 1, 1, 0), #E
    (1, 1, 1, 1) #F
]

code_lst = [ [ [-1]*5 for _ in range(5)] for _ in range(5)]
code_lst[2][1][1] = 0
code_lst[2][2][1] = 1
code_lst[1][2][2] = 2
code_lst[4][1][1] = 3
code_lst[1][3][2] = 4
code_lst[2][3][1] = 5
code_lst[1][1][4] = 6
code_lst[3][1][2] = 7
code_lst[2][1][3] = 8
code_lst[1][1][2] = 9

binlst = [ [0] * 2000 for _ in range(2000)]
code = [0] * 8
codeidx = 7

def hex_to_ten(ch):
    if ord('0') <= ord(ch) <= ord('9'):
        return ord(ch) - ord('0')
    return ord(ch)-ord('A')+10

def check_code() -> int:
    r1 = code[0] + code[2] + code[4] + code[6];
    r2 = code[1] + code[3] + code[5];
    r3 = code[7];
    if ((r1*3 + r2 + r3) %10 == 0): return r1 + r2 + r3
    return 0


T = int(input())
for tc in range(1, T+1):
    N, M = map(int,input().split())
    ans = 0
    codeidx = 7
    for r in range(N):
        st = input().rstrip()
        for c in range(M):
            #16진수를 전부 2진수로 변환
            for idx in range(4*c, 4*(c+1)):
                binlst[r][idx] = Hex_to_bin[hex_to_ten(st[c])][idx-4*c]

    for r in range(1, N): #어차피 가장 맨 위는 0
        idx = 4*M - 1
        codeidx = 7
        while idx >= 0:
            if binlst[r][idx] == 1 and binlst[r-1][idx] == 0:
                n3, n2, n1 = 0, 0, 0
                while binlst[r][idx] == 1:
                    n3+=1
                    idx-=1
                while binlst[r][idx] == 0:
                    n2+=1
                    idx-=1
                while binlst[r][idx] == 1:
                    n1+=1
                    idx-=1
                idx+=1
                minval = min(n3, n2, n1)
                n3 //= minval
                n2 //= minval
                n1 //= minval
                dec = code_lst[n1][n2][n3]
                if dec == -1:
                    codeidx = 7
                else:
                    code[codeidx] = dec
                    codeidx-=1
                    if codeidx == -1:
                        ans += check_code()
                        codeidx = 7
            idx-=1
    print(f'#{tc} {ans}')
