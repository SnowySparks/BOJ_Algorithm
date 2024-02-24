#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define f(a,b,c) for(int a = b; a < c ; ++a)

int n, m, h; //세로선 갯수(열 갯수), 가로선 입력갯수, 사다리 높이
bool gh[12][32]; // [a][b] -> 높이 a, 세로선 번호가 b에서 true면 해당 위치는 다음
int ans = 4; //3이하 아니면 -1이나 마찬가지..
bool fd =false;
int simulation(int x) { //x 위치 시작 
    int now_h = 1;
    while (now_h <= h) {
        if (gh[x][now_h]) ++x;
        else if (gh[x-1][now_h]) --x;
        ++now_h;
    }
    return x;
}

//모든 세로선에 대해서 자기자신으로 돌아가는지 테스트하는 함수
bool test() {
    for (int i = 1; i <= n; ++i) {
        if (simulation(i) != i) return false;
    }
    return true;
}

//추가 설치한 갯수, 최대 설치 갯수, 세로선 탐색 시작위치
void back_track(int total, int max_choice, int start_l, int start_h) {
    if (fd) return;
    if (total == max_choice) {
        if (test()) {
            fd = true;
            ans = total;
        }
        return;
    }
    if (fd) return;

//어차피 같은곳 2개 이상 설치하는 것이 의미가 없음
    for (int h_loc = start_h; h_loc <= h; ++h_loc) {
        int left_loc = (h_loc == start_h ? start_l : 1);
        for (;left_loc < n; ++ left_loc) {
            if (gh[left_loc-1][h_loc] || gh[left_loc][h_loc]  || gh[left_loc+1][h_loc] ) continue;
            gh[left_loc][h_loc] = true;
            back_track(total+1, max_choice, left_loc+1, h_loc);
            if (fd) return;
            gh[left_loc][h_loc] = false;
        }
    }
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> h;
    for (int i = 1; i <= n; ++i) gh[i][h+1] = i; //가장밑바닥 설정
    for (int i = 1; i <= m ; ++i ) {
        int a, b; cin >> a >> b; //높이위치, 왼쪽 
        gh[b][a] = true;
    }
    for (int i = 0; i <= 3; ++i) {
        back_track(0, i, 1, 1);
    }
    cout <<(ans > 3 ? -1 : ans);
    return 0;
}