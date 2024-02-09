#include <iostream>
using namespace std;
const int min_val = -(1e9 + 10);
const int max_val = 1e9 + 10;
int N; //수 갯수
int arr[12]; //수 입력
int oper[4]; //operator + - * / 각각 갯수
int ans_min, ans_max;//답의 최소, 최대값
int all_oper_count; //모든 연산의 총합
void dfs(int total, int cnt) { //연산 결과, 현재까지 사용한 연산자 수

    //모든 연산자 다 사용한 경우
    if (cnt == all_oper_count) {
        ans_min = min(ans_min, total);
        ans_max = max(ans_max, total);
        return;
    }

    //아닌경우
    // add
    if (oper[0]) {
        --oper[0];
        dfs(total + arr[cnt+1], cnt+1);
        ++oper[0];
    }

    // sub
    if (oper[1]) {
        --oper[1];
        dfs(total - arr[cnt+1], cnt+1);
        ++oper[1];
    }

    // mul
    if (oper[2]) {
        --oper[2];
        dfs(total * arr[cnt+1], cnt+1);
        ++oper[2];
    }

    // div
    if (oper[3]) {
        --oper[3];
        dfs(total / arr[cnt+1], cnt+1);
        ++oper[3];
    }
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        //초기화
        ans_min = max_val;
        ans_max = min_val;
        all_oper_count = 0;

        //input
        cin >> N;
        for (int i = 0 ; i < 4; ++i) {
            cin >> oper[i];
            all_oper_count+= oper[i];
        }
        for (int i = 0 ; i < N; ++i) cin >> arr[i];

        //dfs
        dfs(arr[0], 0);

        cout << '#' << tc << ' ' << (ans_max - ans_min) << '\n';
    }
    return 0;
}