#include <iostream>
#include <vector>
#include <cstring>
#define f(a,b,c) for(int a=b;a<c;++a)
using namespace std;

int n, m, k, timer = 0, left_shark;
struct SHARK {
    int r, c, dir; bool isdead = false;
    SHARK(int r = 0, int c = 0, int dir = 0, bool isdead =false) : r(r), c(c), dir(dir),isdead(isdead) {}
};
struct SMELL {
    int left, num;
    SMELL(int left = 0, int num = 0) : left(left), num(num) {}
};

//1 - up, 2 - down, 3 - left, 4-right
int dr[] = {0,-1,1,0,0};
int dc[] = {0,0,0,-1,1};

//정보 입력 칸
int priority_dir[401][5][4]; //[shark_num][now_dir] = [priority dir value]
SMELL smell[20][20];
int loc[20][20];
SHARK shark[401];

void set_smell() {
    f(i,1,m+1) {
        if (shark[i].isdead) continue;
        smell[ shark[i].r ][ shark[i].c ].left = timer+k;
        smell[ shark[i].r ][ shark[i].c ].num = i;
    }
}

void now_smell() {
    f(i,0,n) {
        f(j,0,n) {
            cout << smell[i][j].num << smell[i][j].left <<"\t|";
        }
        cout <<'\n';
    }
}

bool isin(int r, int c) {
    if (r < 0 || c < 0 || r >=n || c >= n) return false;
    return true;
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    left_shark = m;
    //shark loc input   
    f(i,0,n) {
        f(j,0,n) {
            int &e = loc[i][j];
            cin >> e;
            if (e) {
                shark[e].r = i; shark[e].c = j;
            }
        }
    }

    //shark dir input
    f(i,1,m+1) cin >> shark[i].dir;

    //shark priority _dir input
    f(i,1,m+1) {
        f(j,1,5) {
            f(k,0,4) cin >> priority_dir[i][j][k];
        }
    }

    while (timer <= 1000 && left_shark > 1) {
        set_smell();
        f(shark_num, 1, m+1) {
            if (shark[shark_num].isdead) continue;
            int r = shark[shark_num].r , c = shark[shark_num].c, dir = shark[shark_num].dir;
            //냄새 안나는 방향으로 먼저 탐색
            bool ischeck = false;
            f(i,0,4) {
                int nxt_dir = priority_dir[shark_num][dir][i]; //최우선순위부터 탐색
                int nr = r + dr[nxt_dir], nc = c + dc[nxt_dir];
                if (isin(nr,nc) && smell[nr][nc].left <= timer) {  
                    if (loc[nr][nc] == 0) { //상어없음 -> 이동
                        swap(loc[nr][nc],loc[r][c]);
                        shark[shark_num].r = nr; shark[shark_num].c = nc;
                        shark[shark_num].dir = nxt_dir;
                    }
                    else { //상어있음. 항상 번호가 작은게 우선적으로 됨 -> 바로 제거
                        shark[shark_num].isdead = true;
                        loc[r][c] = 0;
                        left_shark--;
                    }
                    ischeck = true;
                    break;
                }
            }
            if (ischeck) continue; //처리된 상어. 스킵
            //자기냄새나는 곳 이동 - 다른 상어 있을 가능성 없음
            f(i,0,4) {
                int nxt_dir = priority_dir[shark_num][dir][i]; //최우선순위부터 탐색
                int nr = r + dr[nxt_dir], nc = c + dc[nxt_dir];
                if (isin(nr,nc) && smell[nr][nc].left > timer && smell[nr][nc].num == shark_num) {  
                    if (loc[nr][nc] == 0) { //상어없음 -> 이동
                        swap(loc[nr][nc],loc[r][c]);
                        shark[shark_num].r = nr; shark[shark_num].c = nc;
                        shark[shark_num].dir = nxt_dir;
                    }
                    else { //상어있음. 항상 번호가 작은게 우선적으로 됨 -> 바로 제거
                        shark[shark_num].isdead = true;
                        loc[r][c] = 0;
                    }
                    break;
                }
            }           
        }
        timer++; //타이머 갱신
    }
    if (timer > 1000) cout << -1;
    else cout << timer;
    
    return 0;
}