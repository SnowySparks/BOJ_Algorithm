#include <iostream>
using namespace std;
const int inf = 250003;
using ll = long long;
#define f(a, b, c) for (int a=b;a<c;++a)
ll fact[inf];
int n; ll prime;

//원리
// r - l 의 크기는 곧 최대 - 최소 크기가 고정되어 있음을 이용함
// 총 N개의 수 (1~N) 에서 r - l = k 일때 선택 가능한 순서와 상관없을때,  N - k이다
// Ex : r - l = 2, N = 4 --> (1 ~ 3) (2 ~ 4) 2개
//그리고 그룹 선택 묶고 나머지 숫자들에 포함 모든 정렬들의 경우의 수는 (N - k)!이다
// 그리고 그룹 내에서 순열 경우의 수는 (k+1)!
// r - l의 최대 허용값은 N - 1 임
// 따라서 0 <= k <= N-1에 대해서 (N-k)!(k+1)!(N-k) 경우 전부 다 더한 값이 최종 값이다.
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    fact[1] = 1;
    f(tc, 1, T+1) {
        cin >> n >> prime;
        f(i, 2, n+2) {
            fact[i] = (fact[i-1] * i)%prime; }
        ll ans = 0;
        f(i, 0, n) {
            ans += fact[i+1] * fact[n-i]%prime * (n-i);
            ans%=prime;
        }
        cout << '#' << tc <<' ' <<ans << '\n';
    }
    return 0;
}