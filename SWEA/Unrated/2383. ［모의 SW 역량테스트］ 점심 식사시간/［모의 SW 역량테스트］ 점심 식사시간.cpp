#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define INF 100000000
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
int n;
int people_cnt, stair_cnt;
int peopleloc[10][2], stairloc[2][2], stair_val[2];

int sel1[10], sel2[10], tmp[10];
int s1 = 0, s2 = 0;
int dist(int *loc1, int *loc2) {
    return abs(loc1[0] - loc2[0]) + abs(loc1[1] - loc2[1]) + 1;
}
int ans;


int cal(int *sel, int cnt, int delay) {
    if (cnt == 0) return 0;
    if (cnt <= 3) {
        int mp = -1;
        f(i, 0, cnt) mp = max(mp, sel[i] + delay);
        return mp;
    }
    else {
        f(i, 3, cnt) {
            copy(sel, sel + cnt, tmp);
            sort(tmp, tmp + cnt);
            tmp[i] = max(tmp[i], tmp[i-3] + delay);
        }
        return tmp[cnt-1] + delay;
    }
}

void back_track(int loc) {
    if (loc == people_cnt) {
        ans = min(ans, max(cal(sel1, s1, stair_val[0]), cal(sel2, s2, stair_val[1])));
        return;
    }

    if (s1 && sel1[s1-1] + stair_val[0] >= ans || s2 && sel2[s2-1] + stair_val[1] >= ans) return;
    sel1[s1] = dist(peopleloc[loc], stairloc[0]);
    ++s1;
    back_track(loc + 1);
    --s1;
    sel1[s1] = 0;

    sel2[s2] = dist(peopleloc[loc], stairloc[1]);
    ++s2;
    back_track(loc + 1);
    --s2;
    sel2[s2] = 0;

    return ;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int tmp;
    int n, m, k; //맵 크기, 시물레이션 시간, 미생물 입력갯수
    for (int tc = 1; tc <= T; ++tc) {
        people_cnt = 0; stair_cnt = 0; ans = INF;
        cin >> n;
        f(i, 0, n) {
            f(j, 0, n) {
                cin >> tmp;
                if (tmp == 1) {
                    peopleloc[people_cnt][0] = i;
                    peopleloc[people_cnt][1] = j;
                    ++people_cnt;
                }
                else if (tmp > 1) {
                    stair_val[stair_cnt] = tmp;
                    stairloc[stair_cnt][0] = i;
                    stairloc[stair_cnt][1] = j;
                    ++stair_cnt;
                }
            }
        }
        back_track(0);
        cout << '#' <<tc << ' ' << ans << '\n';
    }
    return 0;
}