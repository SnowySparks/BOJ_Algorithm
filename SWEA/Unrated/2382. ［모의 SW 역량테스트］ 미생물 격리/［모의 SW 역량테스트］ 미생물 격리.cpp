#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

int arr[100][100];
int mv[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct info {
    int r, c, cells, dir;
    bool operator<(const info &other) const {
        return cells < other.cells;
    }
    bool operator>(const info &other) const {
        return cells > other.cells;
    }
};
info dat[1001];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int n, m, k; //맵 크기, 시물레이션 시간, 미생물 입력갯수
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n >> m >> k;
        int time = 0;
        for (int i = 1; i <= k; ++i) {
            cin >> dat[i].r >> dat[i].c >> dat[i].cells >> dat[i].dir;
        }

        while (time < m)
        {
            memset(arr, 0, sizeof(arr));
            sort(dat+1, dat+1+k, greater<>()); //매번 가장 큰 것부터 이동
            for (int i = 1; i <= k; ++i) {
                if (dat[i].cells == 0) break; // 0값은 무시하기
                dat[i].r += mv[dat[i].dir][0]; dat[i].c += mv[dat[i].dir][1];
                if (dat[i].r == 0 || dat[i].r == n-1 || dat[i].c == 0 || dat[i].c == n-1) {
                    dat[i].cells /= 2;
                    if (dat[i].dir == 1) dat[i].dir = 2;
                    else if (dat[i].dir == 2) dat[i].dir = 1;
                    else if (dat[i].dir == 3) dat[i].dir = 4;
                    else dat[i].dir = 3;
                }
                if (dat[i].cells > -1) {
                    if (arr[dat[i].r][dat[i].c] == 0) {
                        arr[dat[i].r][dat[i].c] = i;
                    }
                    else {
                        int idx = arr[dat[i].r][dat[i].c]; //더 큰
                        dat[idx].cells += dat[i].cells;
                        dat[i].cells = 0;
                    }
                }
            }
            ++time;
        }
        int ans = 0;
        for(int i = 1; i <= k; ++i) ans += dat[i].cells;
        cout << '#' << tc <<' ' <<ans <<'\n';
    }
    return 0;
}