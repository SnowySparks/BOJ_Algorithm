#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

bool isprime[2500];

int n;
// 첫번째 입력값에 따라 입력, 예를들어 첫 값이 4이면 first는 짝수, 5이면 홀수를 담는 식 (second)는 그 반대
vector<int> first;
vector<int> second;
vector<int> adj[1010];
int used_right;

int assign[1010]; // 오른쪽 노드는 어떤 노드랑 연결되어있는가?
bool v[1010]; //dfs탐색중 왼쪽방문한 적있는가

bool dfs(int l){
    if (l == 0) return false; // 첫 숫자에 대한 연결은 배제
    // 이분매칭 코드
    for (int &r : adj[l]) {
        if (v[r]) continue;
        v[r] = true;
        if (assign[r] == -1 || dfs(assign[r])) {
            assign[r] = l;
            return true;
        }
    }
    return false;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // 에라토스테네스 체
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    for (int i = 2; i*i <2500; ++i) {
        if (isprime[i]) {
            for (int j = i*i; j < 2500; j+=i) isprime[j] = false;
        }
    }
    int tmp;

    //input
    bool is_firstodd;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        if (i == 0 ) {
            if (tmp&1) is_firstodd = true;
            else is_firstodd = false;
        }

        if (is_firstodd) {
            if (tmp&1)first.push_back(tmp);
            else second.push_back(tmp);
        }
        else {
            if (tmp&1) second.push_back(tmp);
            else first.push_back(tmp);
        }
    }

    // for (int a :first) {
    //     cout << a <<' ';
    // }
    // cout <<'\n';
    // for (int b :second) {
    //     cout << b <<' ';
    // }  
    // cout <<'\n';

    // 홀 짝 개수가 안맞으면 종료 -> 그럼 애초에 소수 짝이 안되니까
    if (first.size() != second.size()) {
        cout << -1; return 0;
    }


    int fir_size = first.size(), sec_size = second.size();
    // 왼쪽 - 오른쪽 덧셈 결과가 소수라면 연결짓기
    for (int i = 0; i < fir_size; ++i) {
        for (int j = 0; j < sec_size; ++j) {
            if (isprime[first[i] + second[j]]) {
                adj[i].push_back(j);
            }
        }
    }

    vector<int> ans;
    // 첫 숫자랑 연결 가능한 오른쪽 숫자를 "미리 지정" 하고 그 이외들을 이분 매칭. (성공하면 그 첫 연결은 성립)
    for (int &f_r : adj[0]) {
        memset(assign, -1, sizeof(assign));
        // 미리 지정해버리기
        assign[f_r] = 0; 
        bool ispossible = true;
        for (int i = 1; i < fir_size; ++i) {
            memset(v, 0, sizeof(v));
            if (!dfs(i)) {
                ispossible = false;
                break;
            }
        }
        if (ispossible) ans.push_back(second[f_r]);
    }

    if (ans.empty()) cout << -1;
    else {
        sort(ans.begin(), ans.end());
        for (int &num : ans) {
            cout << num <<' ';
        }
    }

    return 0;
}
// 중복되지 않는 수들 중 2개 합이 소수가 될려면 일단 무조건 홀 + 짝 형태여야 함을 이용
// 따라서 홀, 짝 나누고 소수 연결 성립 되는 것끼리 노드 연결 한 후
// 첫 숫자가 다른 오른쪽 수에 미리 연결 지정하고 이분매칭