#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    int temp;
    vector<int> data;
    for (int i = 0; i < N; i++) {
        cin >> temp; 
        data.push_back(temp);
    }
    if (N == 1) { cout << 0; return 0; }
    sort(data.begin(), data.end());
    vector<int> exist;
    int answer = 0, cnt = 0;
    temp = 0;
    do {
        exist.clear();
        exist.push_back(0);
        temp = 0;
        cnt = 0;
        for (int i = 0; i < N; i++) {
            temp += data[i];
            if (temp == 100) break;
            exist.push_back(temp);
        }
        for (int i = 0; i < exist.size(); i++) {
            if (exist[i] > 50) break;
            auto it = lower_bound(exist.begin(), exist.end(), 50+exist[i]);
            if (it == exist.end()) continue;
            if ( *it == exist[i] + 50) cnt++;
        }
        answer = max(answer,cnt);
    } while(next_permutation(data.begin(), data.end()));
    cout << answer; return 0;
}