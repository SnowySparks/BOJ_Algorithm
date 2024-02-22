def input_split(idx, val, lc=0, rc=0):
    return int(idx), val, int(lc), int(rc)

def calculator(operand1, operand2, operator):
    if operator == '+':
        return operand1 + operand2
    elif operator == '-':
        return operand1 - operand2
    elif operator == '*':
        return operand1 * operand2
    else:
        return operand1 / operand2

T = 10
for tc in range(1, T+1):
    operator = set(['+', '-', '*', '/'])
    N = int(input())
    parent, values, lefts, rights = [0], [0], [0], [0]
    for _ in range(N):
        par, val, lc, rc = input_split(*input().split())
        parent.append(par)
        values.append(val)
        lefts.append(lc)
        rights.append(rc)
    parent.reverse()
    for idx in parent:
        if values[idx] in operator:
            lc = lefts[idx]
            rc = rights[idx]
            values[idx] = calculator(int(values[lc]), int(values[rc]), values[idx])
    print(f'#{tc} {int(values[1])}')
