#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)

int n, m, t;// 반지름, m개정수각각, t번 query
int offset_rotate[50]; // 0 초과,
deque<int> dq[50];
deque<pair<int ,int> > tmp;

int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void print() {
    f(i, 0, n) {
        f(j, 0, m) cout << dq[i][j] << ' ';
        cout << '\n';
    }

}

bool isContact (int r, int c) { //해당 위치 주변에 동일한 수가 있는가?
    int num = dq[r][c];
    for (auto &[dr, dc] : mv) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= n) continue;
        nc = (nc + m) % m;
        if (num == dq[nr][nc]) return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    cin >> n >> m >> t;
    f(i, 0, n) dq[i].resize(m);
    f(i, 0, n) f(j, 0, m) cin >> dq[i][j];
    int x, d, k;
    while (t--)
    {
        cin >> x >> d >> k; // Input

        if (k > m/2) {
            k = m-k;
            d ^= 1;
        }
        
        // rotate
        for (int i = x-1; i < n; i += x) {
            if (d) {
                f(j, 0, k) {
                    dq[i].push_back(dq[i].front());
                    dq[i].pop_front();
                }
            }
            else {
                f(j, 0, k) {
                    dq[i].push_front(dq[i].back());
                    dq[i].pop_back();
                }                
            }
        }

        // print();
        // cout << "---\n";
        //find 
        int done = false; // 
        f(r, 0, n) {
            f(c, 0, m) {
                bool found =false;
                if (!dq[r][c]) continue; // 0인경우 스킵
                if (!isContact(r, c)) continue; // 주변 동일한 수가 없음.


                // 있을 경우 주변 번호 전부 정리
                done = true;    
                int target_num = dq[r][c];
                tmp.push_back({r, c});
                dq[r][c] = 0;
                while (!tmp.empty())
                {
                    int cr = tmp.front().first, cc = tmp.front().second; tmp.pop_front();
                    for (auto &[dr, dc] : mv) {
                        int nr = cr + dr, nc = cc + dc;
                        if (nr < 0 || nr >= n) continue;
                        nc = (nc + m) % m;
                        if (dq[nr][nc] == target_num) {
                            dq[nr][nc] = 0;
                            tmp.push_back({nr, nc});
                        }
                    }
                }
                
            }
        }

        // 
        if (!done) {
            int cnt = 0, total = 0;
            f(i, 0, n) f(j, 0, m) {
                if (dq[i][j]) ++cnt;
                total += dq[i][j];
            }
            float mean = 1.0 * total / (1.0*cnt);
            f(i, 0, n) f(j, 0, m) {
                if (dq[i][j]) {
                    if (1.0 *dq[i][j] > mean) dq[i][j]--;
                    else if (1.0 *dq[i][j] < mean) dq[i][j]++;
                }
            }
        }
        // print();
        // cout <<"============\n";
    }

    int ans = 0;
    f(i, 0, n) {
        f(j, 0, m) {
            ans += dq[i][j];
        }
    }
    cout << ans;
    return 0;
}