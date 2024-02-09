#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define NONE -1
#define A 0
#define B 1

int D, W, K; // 두께(행크기), 너비(열 크기), 연속길이 수
int arr[13][20]; //보호 필름
int ans = 0;
int change_row[13]; //약품을 쓴 경우에 대해서, -1 이면 사용안함. 0 이면 A 사용, 1이면 B사용
bool isallow(int idx) { //idx 행에 대해서 1 or 0 K개 연속 존재하는가?
    //A - 0
    int cnt = 0;
    for (int row = 0 ; row < D; ++row) {
        if (change_row[row] == NONE) {
            if (arr[row][idx] == A) ++cnt;
            else cnt = 0;
        }
        else {
            if (change_row[row] == A) ++cnt;
            else cnt = 0;
        }
        if (cnt >= K) return true;
    }
    //B - 1
    cnt = 0;
    for (int row = 0 ; row < D; ++row) {
        if (change_row[row] == NONE) {
            if (arr[row][idx] == B) ++cnt;
            else cnt = 0;
        }
        else {
            if (change_row[row] == B) ++cnt;
            else cnt = 0;
        }
        if (cnt >= K) return true;
    }
    return false;
}

bool allcheck(void) { //모든 행에 대한 체크
    for (int i = 0 ; i < W; ++i) {
        if (isallow(i) == false) {
            return false;
        }
    }
    return true;
}

//backtracking 구현
vector<int> lst;
bool fd = false;
void backtracking(int idx, int cnt, int change_val) {
    if (fd) return; //이미 탐색성공한 경우 지체없이 종료
    if (cnt == change_val) {
        //합당한 조합인 경우 탐색 성공 표시
        if (allcheck()) {
            fd = true;
        }
        return;
    }
    if (fd) return; //탐색 성공시 그 즉시 종료 
    for (int i = idx; i < D; ++i) {
        //백트래킹으로 선택되는 위치 및 선택되는 값을 선택
        change_row[i] = A;
        backtracking(i+1,cnt+1,change_val);
        change_row[i] = B;
        backtracking(i+1,cnt+1,change_val);
        change_row[i] = NONE;
    }
    return;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        //초기화
        lst.clear();
        fd = false;
        //입력
        cin >> D >> W >> K;
        for (int i = 0 ; i < D; ++i) change_row[i] = NONE;
        for (int r = 0 ; r < D ; ++r) {
            for (int c = 0 ; c < W ; ++c) {
                cin >> arr[r][c];
            }
        }

        // f(i, 0, W) {
        //     cout << i <<' ' <<isallow(i) <<'\n';
        // }
        // 약품 안쓰고 통과하면 끝
        if (allcheck()) {
            cout << '#' << tc <<' '<<0<<'\n';
            continue;
        }

        //1회이상 시도
        //K-1까지만 탐색 -> 이유 : K번 스왑은 어차피 무조건 되는걸로 보장하니까
        int cntp = 1;
        while (cntp <= K-1) {
            backtracking(0,0,cntp);
            if (fd) break;
            ++cntp;
        }
        cout << '#' << tc <<' ' << cntp << '\n';
    }

    return 0;
}