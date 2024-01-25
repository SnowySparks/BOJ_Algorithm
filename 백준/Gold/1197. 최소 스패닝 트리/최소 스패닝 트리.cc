#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent[10001];
bool is_unioned;
int find(int a) { //Union _Find
    if (parent[a] == a) return a;
    return parent[a] = find(parent[a]); }

void _union(int a, int b) {
    is_unioned = false;
    int pa = find(a);
    int pb = find(b);
    if (pa == pb) {return;}
    parent[max(pa,pb)] = min(pa,pb);
    is_unioned = true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long answer = 0;
    int V, E; cin >> V >> E;
    vector<pair <int, pair<int ,int> > > dt;
    int start, end, cost;
    for (int i = 0; i < E ; i++) {
        cin >> start >> end >> cost;
        dt.push_back({cost, {start, end}});
    }
    sort(dt.begin(), dt.end());
    for (int i = 1 ; i <= V ; i++) parent[i] = i;

    for (auto e : dt) {
        _union(e.second.first, e.second.second);
        if (is_unioned) answer+=e.first;
    }
    cout << answer ; return 0;
}