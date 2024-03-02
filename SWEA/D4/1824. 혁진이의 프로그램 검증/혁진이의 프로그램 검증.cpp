#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#define INF 100000000
#define DOWN 0
#define UP 3
#define LEFT 2
#define RIGHT 1
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
int inp[20][20];
bool v[20][20][16][4]; // R, C, memory_value, direction --> 해당 위치에 memory_value 상태에서 "어느 방향에서 왓는가?"
// ex 오른쪽으로 가서 해당 위치 도착하면 , 도착블럭기준 왼쪽에서 온 것이나 다름없음. 따라서 왼쪽방향에 대한 방문처리함
int mv[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}}; //아래쪽, 오른쪽, 왼쪽, 위쪽

struct io {
    int r, c, memo, dir;
};

// int char_command(char ch) {
//     if (ch == '<') return 2; //왼쪽강제이동
//     else if (ch == '>') return 1; //오른쪾강제 이동
//     else if (ch == '^') return 3; //위로
//     else if (ch == 'v') return 0; //아래로

//     else if (ch == '.') return -1; //방향 꺽기 안함.

//     //조건부 방향 꺽기. 0 이냐 아니냐?
//     else if (ch == '_') return 4; // 0 이면 오른쪽, 아님 왼쪽
//     else if (ch == '|') return 5; // 0 이면 아래쪽, 아님 위쪽

//     else if (ch == '?') return 6; // 4방향 전부 다 탐색

//     else if (ch == '@') return -2; // 종료

//     else if (ch == '+') return 7; // memo = (memo + 1)%16
//     else if (ch == '-') return 8; // memo = (memo + 15)%16
    
//     else return ch - '0' + 10; // 숫자입력
// }

int char_command(char ch) {
    switch (ch)
    {
    case '<':
        return 2;
        break;  
    case '>':
        return 1;
        break;
    case '^':
        return 3;
        break;  
    case 'v':
        return 0;
        break;   
    case '.':
        return -1;
        break;   
    case '_':
        return 4;
        break;   
    case '|':
        return 5;
        break;   
    case '?':
        return 6;
        break;   
    case '@':
        return 9;
        break;   
    case '+':
        return 7;
        break;   
    case '-':
        return 8;
        break;   
    default:
        return ch - '0' + 10;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int R, C;
    string tmp;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> R >> C;
        bool isend = false;
        bool finish = false;
        f(r, 0, R) {
            cin >> tmp;
            f(c, 0, C) {
                inp[r][c] = char_command(tmp[c]);
                if (inp[r][c] == 9) isend = true;
            }   
        }

        //종료 입력 없음 -> 해봤자 의미가 없음
        if (!isend) {
            cout << '#' << tc << " NO\n";
            continue;
        }

        //있으면 시물레이션
        //초기설정
        memset(v, 0, sizeof(v));
        queue<io> q;
        q.push({0, 0, 0, RIGHT}); //가장 좌측 상단. 
        while (!q.empty())
        {   
            int r= q.front().r, c = q.front().c, memo = q.front().memo, dir = q.front().dir;
            q.pop();
            // cout << r <<' ' <<c << ' ' <<memo << ' ' << dir <<'\n';
            
            int command = inp[r][c];

            //종료조건
            if (command == 9) {
                finish = true;
                break;
            }
            else if (command == 6) {
                // cout <<"?\n";
                for (int ndir = 0; ndir < 4; ++ndir) {
                    int nr = (r + mv[ndir][0] + R)%R, nc = (c + mv[ndir][1] + C)%C;
                    // cout << nr << ' ' << nc <<'\n';
                    if (!v[nr][nc][memo][3-ndir]) {
                        v[nr][nc][memo][3-ndir] = true;
                        q.push({nr, nc, memo, ndir});
                    }
                }
            }
            else {
                if (command <= 3 ) {
                    if (command >= 0) dir = command;
                }
                else if (command == 4) dir = (memo == 0 ? RIGHT : LEFT);
                else if (command == 5) dir = (memo == 0 ? DOWN : UP);
                else if (command == 7) memo = (memo + 1)%16;
                else if (command == 8) memo = (memo + 15)%16;
                else memo = command - 10;

                int nr = (r + mv[dir][0] + R)%R, nc = (c + mv[dir][1] + C)%C;
                if (!v[nr][nc][memo][3-dir]) {
                    v[nr][nc][memo][3-dir] = true;
                    q.push({nr, nc, memo, dir});
                }                
            }
        }

        if (finish) cout << '#' << tc << " YES\n";
        else cout << '#' << tc << " NO\n";
    }
    return 0;
}