#include <iostream>
#include <vector>
#include <cstring>
#define f(a, b, c) for (int a=b;a<c;++a)
using namespace std;

int n, m; //도시 총 크기, 한 집 pay양

int house[400][2]; //House Location
int dist_cnt[40];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("sample_input.txt","r",stdin);
    int T; cin >> T;
    int cnt = 0;
    int tmp;
    int max_dst = 0;
    for (int tc = 1; tc <= T; ++tc) {
        cnt = 0;
        max_dst = 0;
        cin >> n >> m;
        memset(house, 0, sizeof(house));

        f(i, 0, n) {
            f(j, 0, n) {
                cin >> tmp;
                if (tmp) {
                    house[cnt][0] = i;
                    house[cnt][1] = j;
                    ++cnt;
                }
            }
        }
        int ans = 1;

        f(i, 0, n) {
            f(j, 0, n) {
                memset(dist_cnt, 0, sizeof(dist_cnt));
                f(idx, 0, cnt) {
                    int dst = abs(i - house[idx][0]) + abs(j - house[idx][1]);
                    dist_cnt[dst]++;
                }
                int prefix = 0;
                f(k, 1, 40) {
                    int cost = k*k + (k-1)*(k-1);
                    prefix += dist_cnt[k-1];
                    if (prefix * m - cost >= 0) ans= max(ans, prefix);
                }
            }
        }
        cout << '#' <<tc <<' ' <<ans <<'\n';
    }
    return 0;
}