#include <iostream>
#include <cstring>
using namespace std;
#define f(a, b, c) for (int a = b; a<c; ++a)
int n, x;
int arr[100][100];

int dr[] = {0, 1};
int dc[] = {1, 0};

bool ispossible(int sr, int sc, int dir) { //해당 방향으로 활주로 건설이 가능한지 판단하는 함수
    //첫 블럭에 대한 정보 등록
    int now_num=arr[sr][sc];
    int before_num = arr[sr][sc];
    int cnt = 1;
    bool need_install = false;
    bool before_1_install = false; //만약 x 가 1일때 쓰는 장치
    //2번째 ~ N번째 블럭에 대한 탐색
    for(int r = sr +dr[dir], c = sc + dc[dir], idx = 1; r < n && c <n; r+=dr[dir], c+=dc[dir], ++idx) {
        before_num = now_num;
        now_num = arr[r][c];
        //직전 블럭이랑 현재 블럭이랑 같은 높이이면 -> 연속갯수이니 카운팅
        if (now_num == before_num) {
            ++cnt;
            before_1_install = false;
            if (need_install && cnt==x) { //만약 직전에 설치를 해야하는 상태인데 조건에 만족하면
            //그 즉시 설치 불필요 상태로 만들고 카운팅을 다시 0으로 리셋으로만든다
                need_install = false;
                cnt =0;
            }
        }
        //현재 높이가 1칸 더 높은경우
        else if (now_num - before_num == 1) {
            if (cnt >= x) { //직전에 이미 동일한 높이가 x개 이상 있으면 다시 자기 블럭으로 초기화 함
                if(x == 1 && cnt == 1 && before_1_install) return false;
                before_1_install =false;
                cnt = 1;
            }
            else { //충분치 못한 동일한 크기길이 이므로 그 즉시 종료
                return false;
            }
        }

        else if (now_num - before_num == -1) { //직전 블록이 한칸 더 높을 때
            //설치가 필요한 상황인데, 길이도 부족하면 그 즉시 종료 ex 5 4 3 2 1 상태
            if (need_install && cnt < x) return false;
            //만족할 경우 혹은 평지였었던 경우 -> 활주로 설치가 필요하다고 판단후 다시 1로 재 카운팅
            need_install = true;
            cnt = 1;
            if (x == 1) before_1_install = true;
        }
        //크기 2차이는 답없다...
        else if (abs(now_num-before_num) >= 2) {
            return false;}

        //마지막 인덱스값에 대한 중요처리 Ex : 4 4 4 4 4 3
        if (idx == n-1 && need_install ) {
            if (cnt < x) {
                return false;
            }
        }
    }
    // 모든 극악의 조건을 다 뚫으면 해당 라인은 활주로 건설이 가능함
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    f(tc, 1, T+1) {
        cin >> n >> x;
        f(r, 0, n) {
            f(c, 0, n) {
                cin >> arr[r][c];
            }
        }
        int ans = 0;
        f(r, 0, n) {
            ans += (ispossible(0,r,1) ? 1 : 0);
            ans += (ispossible(r,0,0) ? 1 : 0);
        }
        cout << '#' << tc <<' ' << ans<<'\n';
    }
    return 0;
}