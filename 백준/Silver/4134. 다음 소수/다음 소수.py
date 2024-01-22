import sys
input = sys.stdin.readline

def isprime(n):
    if n <= 1 : return False
    for i in range(2, int(n**(0.5)+1)):
        if n%i == 0 : return False
    return True

t = int(input().rstrip())

for i in range(t):
    p = int(input().rstrip())
    if (p == 0 or p == 1) : print(2)
    else :
        while True:
            if isprime(p):
                print(p)
                break
            p+=1
