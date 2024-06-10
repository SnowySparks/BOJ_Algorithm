#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)

int n, m, t;// 반지름, m개정수각각, t번 query
int arr[50][50];
int tmp[50];
deque<pair<int ,int> > dq;

int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void print() {
    f(i, 0, n) {
        f(j, 0, m) cout << arr[i][j] << ' ';
        cout << '\n';
    }

}

bool isContact (int r, int c) { //해당 위치 주변에 동일한 수가 있는가?
    int num = arr[r][c];
    for (auto &[dr, dc] : mv) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= n) continue;
        nc = (nc + m) % m;
        if (num == arr[nr][nc]) return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    cin >> n >> m >> t;
    f(i, 0, n) f(j, 0, m) cin >> arr[i][j];
    int x, d, k;
    while (t--)
    {
        cin >> x >> d >> k; // Input

        // rotate
        for (int i = x-1; i < n; i += x) {
            f(j, 0, m) tmp[(j + (d == 0 ? k : m-k))%m] = arr[i][j];
            copy(tmp, tmp+m, arr[i]);
        }

        // print();
        // cout << "---\n";
        //find 
        int done = false; // 
        f(r, 0, n) {
            f(c, 0, m) {
                bool found =false;
                if (!arr[r][c]) continue; // 0인경우 스킵
                if (!isContact(r, c)) continue; // 주변 동일한 수가 없음.


                // 있을 경우 주변 번호 전부 정리
                done = true;    
                int target_num = arr[r][c];
                dq.push_back({r, c});
                arr[r][c] = 0;
                while (!dq.empty())
                {
                    int cr = dq.front().first, cc = dq.front().second; dq.pop_front();
                    for (auto &[dr, dc] : mv) {
                        int nr = cr + dr, nc = cc + dc;
                        if (nr < 0 || nr >= n) continue;
                        nc = (nc + m) % m;
                        if (arr[nr][nc] == target_num) {
                            arr[nr][nc] = 0;
                            dq.push_back({nr, nc});
                        }
                    }
                }
                
            }
        }

        // 
        if (!done) {
            int cnt = 0, total = 0;
            f(i, 0, n) f(j, 0, m) {
                if (arr[i][j]) ++cnt;
                total += arr[i][j];
            }
            float mean = 1.0 * total / (1.0*cnt);
            f(i, 0, n) f(j, 0, m) {
                if (arr[i][j]) {
                    if (1.0 *arr[i][j] > mean) arr[i][j]--;
                    else if (1.0 *arr[i][j] < mean) arr[i][j]++;
                }
            }
        }
        // print();
        // cout <<"============\n";
    }

    int ans = 0;
    f(i, 0, n) {
        f(j, 0, m) {
            ans += arr[i][j];
        }
    }
    cout << ans;
    return 0;
}