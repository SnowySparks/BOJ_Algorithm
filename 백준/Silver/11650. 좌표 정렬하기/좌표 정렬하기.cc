#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

bool comp(const pair<int,int>& a, const pair<int,int>& b) {
    return a.first == b.first ? a.second < b.second : a.first < b.second;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    vector<pair<int,int> > v;
    pair<int,int> temp;
    while (N--) {
        cin >> temp.first >> temp.second;
        v.push_back(temp);
    }

    sort (v.begin(),v.end());

    for (auto e : v) {
        cout << e.first << " " << e.second <<'\n';
    }
    return 0;

}
