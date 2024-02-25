#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define f(a,b,c) for (int a=b;a<c;a++)

#define CORE 1
#define LINE 2
#define EMPTY 0
#define MAXLINE 0x7f7f7f7f

int N;
int arr[12][12];
int max_core = 0, min_line = MAXLINE;
bool connected[12];
int process_loc[12][2]; //12개가 최대
int process_cnt = 0;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

bool can_connect(int r, int c, int dir) {
    int nr = r + dr[dir], nc = c +dc[dir];
    while (true) {
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
        if (arr[nr][nc] != EMPTY) return false;
        nr += dr[dir]; nc+=dc[dir];
    }
    return true;
}

int set_line(int r, int c, int dir, int block = 2) {
    int nr = r + dr[dir], nc = c +dc[dir], cnt = 0;
    while (true) {
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
        ++cnt;
        arr[nr][nc] = block;
        nr += dr[dir]; nc+=dc[dir];
    }
    return cnt;
}

void back_track(int cnt, int loc, int line) { //현재 추가로 연결한 프로세서 수, 탐색시작위치, 연결된 라인 수
    //답 갱신
    if (max_core < cnt) {
        max_core = cnt;
        min_line = line;
    }
    else if (cnt == max_core &&  line < min_line) {
        min_line = line;
    }
    //탐색 종료 조건
    if (loc == process_cnt) return;

    //남은 탐색해야 할 프로세스 크기 + 이미 연결된 수가 답보다 작거나 같은데도
    //이미 라인이 답모다 크거나 같으면 탐색 의미가 없음.
    if (process_cnt - loc + cnt < max_core || process_cnt - loc + cnt == max_core && line >= min_line ) return; 
    
    //사방탐색
    for (int i = loc; i < process_cnt; ++i) {
        for (int dir = 0; dir < 4; ++dir) {
            if (can_connect(process_loc[i][0], process_loc[i][1], dir)) {
                int add_line = set_line(process_loc[i][0], process_loc[i][1], dir, LINE);
                back_track(cnt+1, i+1, line+add_line);
                set_line(process_loc[i][0], process_loc[i][1], dir, EMPTY);
            }
        }
    }
    return;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> N;
        //초기화
        max_core = 0; min_line = MAXLINE; process_cnt = 0; memset(connected, 0, sizeof(connected));
        f(r, 0 , N) {
            f(c, 0, N) {
                cin >> arr[r][c];
                if (arr[r][c]) {
                    //겉에 이미 연결되어 있는 건 무시
                    if (r == 0 || r == N-1 || c == 0 || c ==N-1) continue;
                    //연결 안된 프로세서만 등록 밑 카운팅
                    process_loc[process_cnt][0] = r;
                    process_loc[process_cnt][1] = c;
                    ++process_cnt;
                }
            }
        }
        //백트래킹
        back_track(0, 0, 0);
        cout << '#' << tc << ' ' << min_line <<'\n';
    }

    return 0;
}