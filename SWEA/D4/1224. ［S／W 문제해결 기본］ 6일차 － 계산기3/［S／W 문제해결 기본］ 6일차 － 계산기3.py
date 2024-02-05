# import sys
from collections import deque

# sys.stdin = open('input.txt', 'r')


def operator_priority(op: str) -> int:
    if op == '+' or op == '-':
        return 0
    elif op == '*' or op == '/':
        return 1
    return -1


def operating(a: int, b: int, op: str) -> int:
    if op == '+':
        return a + b
    elif op == '-':
        return a - b
    elif op == '*':
        return a * b
    else:
        return a // b


def postfix(m_fix: str) -> str:
    lst = []
    stack = deque()

    for ch in m_fix:
        if ch.isdecimal():
            lst.append(ch)
        elif ch =='(':
            stack.append(ch)
        elif ch == ')':
            while stack and stack[-1] != '(':
                lst.append(stack.pop())
            stack.pop()
        else:
            while stack and operator_priority(stack[-1]) >= operator_priority(ch):
                lst.append(stack.pop())
            stack.append(ch)
    while stack:
        lst.append(stack.pop())
    return ''.join(lst)


def calc(p_fix: str) -> int:
    res = 0
    stack = deque()
    for ch in p_fix:
        if ch.isdecimal():
            stack.append(ord(ch) - ord('0'))
        else:
            n2 = stack.pop()
            n1 = stack.pop()
            stack.append(operating(n1, n2, ch))
    return stack[-1]


T = 10
for tc in range(1, T + 1):
    num = int(input())
    inp = input()
    print(f'#{tc} {calc(postfix(inp))}')
