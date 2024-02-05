#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define f(a,b,c) for(int a = b; a < c ; ++a)

int R, C, M; //total row, colum, shark_num

struct SHARK {
    int r, c, s, d, z;
    bool isdead = false;
    //row, col, speed, dir, size
};

// 위 아래 오른쪽 왼쪽 
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, 1, -1};

SHARK shark[10001];
int gh[100][100]; //상어 위치
int ngh[100][100];

int fishing(int loc) { //낚시
    f(i,0,R) {
        if (gh[i][loc] > 0 && shark[gh[i][loc]].isdead == false) {
            int fd = gh[i][loc];
            shark[fd].isdead = true;
            gh[i][loc] = 0;
            return shark[fd].z;
        }
    }
    return 0;
}

void moving() {
    memset(gh,0,sizeof(gh));
    f(num, 1, M+1) {
        if (shark[num].isdead) continue; //죽은 상어는 스킵
        int r = shark[num].r, c=shark[num].c , dir = shark[num].d , s = shark[num].s;
        
        //행 이동
        if (dir == 1 || dir == 2) {
            int mvr = s % (2 * (R -1)); //2*(R-1)만큼 이동시 제자리 + 방향 그대로
            if (dir == 1) { //처음 방향 -> 위쪽일 때 
                if (mvr <= r) {
                    r-=mvr;
                }
                else if (mvr < r + R) {
                    dir = 2;
                    r = (mvr-r);
                }
                else r = 2*R + r - 2 - mvr;
            }
            else {
                if (mvr <= R-1-r) {
                    r+=mvr;
                }
                else if (mvr <= 2*(R-1)-r) {
                    dir = 1;
                    r = 2*(R-1)-mvr-r;
                }
                else r = mvr - (2*(R-1) - r);             
            }
        }
        //열 이동
        if (dir == 3 || dir == 4) {
            int mvr = s % (2 * (C -1)); 
            if (dir == 4) { 
                if (mvr <= c) {
                    c-=mvr;
                }
                else if (mvr < c + C) {
                    dir = 3;
                    c = (mvr-c);
                }
                else c = 2*C + c - 2 - mvr;
            }
            else {
                if (mvr <= C-1-c) {
                    c+=mvr;
                }
                else if (mvr <= 2*(C-1)-c) {
                    dir = 4;
                    c = 2*(C-1)-mvr-c;
                }
                else c = mvr - (2*(C-1) - c);             
            }
        }
        shark[num].r = r; shark[num].c = c; shark[num].d = dir;
        //상어 잡아먹기
        if (gh[r][c] == 0) {
            gh[r][c] = num;
        }
        else {
            if (shark[num].z > shark[gh[r][c]].z) {
                shark[gh[r][c]].isdead=true;
                gh[r][c] = num;
            }
            else {
                shark[num].isdead=true;
            }
        }
    }
    // f(i,0,R) {
    //     f(j,0,C) {
    //         cout << gh[i][j] <<' ';
    //     }
    //     cout << '\n';
    // }
    // cout << "\n----\n";
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> R >> C >> M;
    f(i,1,M+1) {
        cin >> shark[i].r >> shark[i].c >> shark[i].s >> shark[i].d >> shark[i].z;
        --shark[i].r; --shark[i].c;
        gh[shark[i].r][shark[i].c] = i;
    }
    int ans = 0;
    f(idx, 0, C) { //idx : 낚시부 - moving
        //2. fishing
        ans += fishing(idx);
        //3. moving
        moving();
    }
    cout << ans;
    return 0;
}