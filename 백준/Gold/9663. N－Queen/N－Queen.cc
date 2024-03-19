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
        if (row[r]) continue;
        if (rightup[ru] || leftup[lu]) continue;
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
    scanf("%d", &n);
    dfs(0);
    printf("%d", total);
    return 0;
}