#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
const int MAX_N = 80000;
int arr[MAX_N];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    // input
    int N; cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    long long answer = 0; // 정답

    stack<int> st;

    for(int i = 0; i < N; i++) {
        while(!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        answer += st.size();
        st.push(arr[i]);
    }
    cout << answer;
    return 0;
}