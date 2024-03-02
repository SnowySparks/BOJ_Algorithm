#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define WHITE 0
#define RED 1
#define BLUE 2
#define f(a, b, c) for(int a =b;a < c; ++a)
using namespace std;

int n, k;
int mv[5][2] = {{0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int rev[5] = {0, 2, 1, 4, 3}; // 뒤집었을 경우 방향
int gh[14][14]; //색 정보 입력
struct info {
    int r, c, dir;
};
info dt[11];
vector<int> state[14][14]; // 말 이동 정보
vector<int> temp_lst; //임시 배열

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    f(i, 1, n+1) {
        f(j, 1, n+1) {
            cin >> gh[i][j];
        }
    }

    f(i, 0, n+2) {
        gh[0][i] = BLUE;
        gh[n+1][i] = BLUE;
        gh[i][0] = BLUE;
        gh[i][n+1] = BLUE;
    }

    f(i, 1, k+1) {
        cin >> dt[i].r >> dt[i].c >> dt[i].dir;
        state[dt[i].r][dt[i].c].push_back(i);
    }

    //이미 만족을 한 경우.
    f(i, 1, k+1) {
        if (state[dt[i].r][dt[i].c].size() >= 4) {
            cout << 0;
            return 0;
        }
    }
    bool end = false;
    int t = 0; // t번째 턴
    while (true)
    {   
        f(i, 1, k+1) {
            if (state[dt[i].r][dt[i].c].size() >= 4) {
                end = true;
                break;
            }
        }
        if (end) break;
        ++t;
        if (t > 1000) break;
        f(i, 1, k+1) { // i 번 말 이동
            int r = dt[i].r, c = dt[i].c, dir = dt[i].dir; //기존 위치
            int nr = r + mv[dir][0], nc = c + mv[dir][1]; // 이동할 위치
            int floor = find(state[r][c].begin(), state[r][c].end(), i) - state[r][c].begin(); // 말 층 위치
            int tmp = (int)state[r][c].size(); // 현재 움직이여 야 하는 말 위치의 전체 층 높이 
            //이동할 위치가 WHITE인 경우 -> 그대로 순위 유지한 채로 옮기기
            if (gh[nr][nc] == WHITE) {
                f(k, floor, tmp) {
                    int ids = state[r][c][k];
                    dt[ids].r = nr;
                    dt[ids].c = nc;
                    state[nr][nc].push_back(state[r][c][k]);
                    if (state[nr][nc].size() >= 4) {
                        end = true;
                        break;
                    }
                }
                f(k, floor, tmp) state[r][c].pop_back();
            }
            else if (gh[nr][nc] == RED) {
                f(k, floor, tmp) {
                    int ids = state[r][c].back();
                    dt[ids].r = nr;
                    dt[ids].c = nc;
                    state[nr][nc].push_back(ids);
                    state[r][c].pop_back();
                    if (state[nr][nc].size() >= 4) {
                        end =true;
                        break;
                    }
                }
            }
            else {
                int new_dir = rev[dir];
                nr = r + mv[new_dir][0];
                nc = c + mv[new_dir][1];
                dt[i].dir = new_dir;
                if (gh[nr][nc] == WHITE) {
                    f(k, floor, tmp) {
                        int ids = state[r][c][k];
                        dt[ids].r = nr;
                        dt[ids].c = nc;
                        state[nr][nc].push_back(state[r][c][k]);
                        if (state[nr][nc].size() >= 4) {
                            end = true;
                            break;
                        }
                    }
                    f(k, floor, tmp) state[r][c].pop_back();
                }

                else if (gh[nr][nc] == RED) {
                    f(k, floor, tmp) {
                        int ids = state[r][c].back();
                        dt[ids].r = nr;
                        dt[ids].c = nc;
                        state[nr][nc].push_back(ids);
                        state[r][c].pop_back();
                        if (state[nr][nc].size() >= 4) {
                            end =true;
                            break;
                        }
                    }
                }
                else {
                    continue;
                }
            }
            if (end) break;
        }
        if (end) break;
    }
    if (t <= 1000) cout << t;
    else cout << -1;
    return 0;
}