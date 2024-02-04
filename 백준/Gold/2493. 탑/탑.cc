#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define f(a,b,c) for (int a=b;a<c;++a)
const int mv = 5e5+1;
int n, arr[mv], ans[mv];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i,1,n+1) cin >> arr[i];
    stack<int> st;
    f(i,1,n+1) {
        while(!st.empty() && arr[st.top()] < arr[i]) st.pop();
        ans[i] = (st.empty() ? 0 : st.top());
        st.push(i);
    }
    f(i,1,n+1) cout << ans[i] <<' ';
}