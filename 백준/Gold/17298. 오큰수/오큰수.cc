#include <iostream>
#include <stack>
#include <string>

using namespace std;

int arr[1000001];
int seq[1000001];

int main(void) {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    stack <int> s;
    int N;
    cin >> N;

    for (int i=1 ; i<=N ; i++) {
        cin >> arr[i];
    }


    for (int i= N ; i>=1 ; i--) {
        while ((!s.empty()) && (s.top() <= arr[i])) {
            s.pop();
        }
        if (s.empty()) {
            seq[i]=-1;
            s.push(arr[i]);
        }
        else {
            seq[i] = s.top();
            s.push(arr[i]);
        }
    }

    for (int i=1 ; i<=N ; i++) {
        cout << seq[i] << " ";
    }
    return 0;

}
    

 