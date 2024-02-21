T = 10
for tc in range(1, T+1):
    N = int(input())
    left = [0] * (N+1)
    right = [0] * (N + 1)
    parent = [0] * (N + 1)
    sentence = [0] * (N + 1)
    sentence_idx = []

    def atoi(par, lc, rc):
        return int(par), int(lc), int(rc)

    def make_tree(par, word, lc='0', rc='0'):
        par, lc, rc = atoi(par, lc, rc)
        sentence[par] = word
        if lc != 0:
            left[par] = lc
            parent[lc] = par
        if rc != 0:
            right[par] = rc
            parent[rc] = par

    def inorder(T):
        if T:
            inorder(left[T])
            sentence_idx.append(T)
            inorder(right[T])

    for _ in range(N):
        make_tree(*list(map(str, input().split())))

    inorder(1)

    print(f'#{tc}', end=' ')
    for idx in sentence_idx:
        print(sentence[idx], end='')
    print()
