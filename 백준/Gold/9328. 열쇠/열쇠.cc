#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#define f(a, b, c) for (int a = b; a < c; ++a)
using namespace std;

int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int h, w; //행 크기, 열 크기
char inp[102][102];
bool v[102][102];
int cnt = 0;
char inp_key[26];

// 방문 전 문 위치
vector<pair<int, int> > door_list[26];
bool unlock[26];

int main(void) {
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--)
    {
        // input. 맵 크기 및 맵 정보 입력
        cin >> h >> w;
        f(i, 1, h + 1) {scanf("%s", inp[i]+1);}
        f(i, 0, w + 2) {inp[0][i] = '.'; inp[h+1][i] ='.';}
        f(i, 0, h + 2) {inp[i][0] = '.'; inp[i][w+1] = '.';}

        f(i, 0, 26) door_list[i].clear();
        memset(unlock, 0, sizeof(unlock));
        memset(v, 0, sizeof(v));

        // 이미 열쇠가 존재한다면 열쇠 소유 표시
        scanf("%s", inp_key);
        if (inp_key[0] != '0') {
            for (int i = 0; i < 30; ++i) {
                if (inp_key[i] == '\0') break;
                unlock[inp_key[i]-'a'] = true;
            }
        }
        int ans = 0;
        queue<pair<int ,int> > q;
        q.push({0, 0});
        v[0][0] = true;

        while (!q.empty())
        {   
            int r = q.front().first, c =q.front().second; q.pop();

            for (auto &[dr, dc] : mv) {
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nc < 0 || nr >= h+2 || nc >= w+2 || v[nr][nc] || inp[nr][nc] == '*') continue;
                if (inp[nr][nc] >= 'A' && inp[nr][nc] <= 'Z') {
                    int idx = inp[nr][nc] - 'A';
                    if (unlock[idx]) {
                        q.push({nr, nc});
                        v[nr][nc] = true;
                    }
                    else {
                        door_list[idx].push_back({nr, nc});
                    }
                }

                else if (inp[nr][nc] >= 'a' && inp[nr][nc] <= 'z') {
                    int idx = inp[nr][nc] - 'a';
                    q.push({nr, nc});
                    v[nr][nc] = true;
                    if (!unlock[idx]) {
                        unlock[idx] = true;
                        for (auto &[mr, mc] : door_list[idx]) {
                            q.push({mr, mc}); v[mr][mc] = true;
                        }
                    }
                }

                else if (inp[nr][nc] =='$') {
                    v[nr][nc] = true;
                    ans += 1;
                    q.push({nr, nc});
                }
                else {
                    v[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}