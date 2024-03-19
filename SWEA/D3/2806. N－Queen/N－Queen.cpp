#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool row[16];
bool leftup[31];
bool rightup[31];
int total = 0;
int n;
void dfs(int col) {
    if (col == n) {
        ++total;
        return;
    }

    for (int r = 0; r < n; ++r) {
        int ru = r + col, lu = (n - 1) - (r - col);
        if (row[r] ||rightup[ru] || leftup[lu]) continue;
        row[r] = true;
        leftup[lu] = true;
        rightup[ru] = true;
        dfs(col + 1);
        row[r] = false;
        leftup[lu] = false;
        rightup[ru] = false;        
    }
}

int main(void) {
    int T; scanf("%d", &T);
    for (int tc = 1; tc <= T; ++ tc) {
        scanf("%d", &n);
        total = 0;
        dfs(0);
        printf("#%d %d\n",tc, total);
    }
    return 0;
}

// 원리
// 대각선 (y=x), (y=-x)이 같은 위치인 경우 특수한 연산값이 전부 같음
// y=x 방향 : (r + c), y=-x 방향 : ( (n-1) - (r-c) )