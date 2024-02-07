#include <iostream>
#include <stack>
using namespace std;
using ll = long long;
const int inf = 1e5+2;
ll arr[inf];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    stack<int> st;
    int n; cin >> n;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    st.push(0);
    
    //단조 수열을 이용. - 스택할 수록 내림차순으로
    //너비(width) 계산을 용이하기 위해서 인덱스를 이용
    // (i - stack에 담긴 인덱스값) * arr[stack에 담긴 인덱스값] -> 넓이

    for (int i = 1; i <= n+1; ++i) {
        while( !st.empty() && arr[st.top()] > arr[i]) {
            ll loc = st.top(); st.pop();
            ans = max(ans, arr[loc]*(i -st.top() -1));
            //굳이 해당 높이 idx를 pop하고 너비는 그 다음 것을 사용하는 이유
            //최종적으로 1 * n 도 계산하기 위함
        }
        st.push(i);
    }
    cout << ans;
    return 0;
}