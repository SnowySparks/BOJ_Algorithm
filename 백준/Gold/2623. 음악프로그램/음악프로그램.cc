#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++)
int n, m;
vector<int> gh[1001];
vector<int> ans;
int indegree[1001];
bool v[1001];
int ord[100];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    f(i,0,m) {
        int p; cin >> p;
        f(k,0,p) {
            cin >> ord[k];
            if (k>=1) {
                gh[ord[k-1]].push_back(ord[k]);
                indegree[ ord[k] ]++;
            }
        }
    }
    queue<int> q;

    f(i,1, n+1) {
        if (indegree[i]==0 ) q.push(i);     
    }

    while (!q.empty()) {
        int loc = q.front(); q.pop();
        ans.push_back(loc);
        for (int e : gh[loc]) {
            indegree[e]--;
            if (indegree[e] == 0) q.push(e);
        }
    }

    if (ans.size() != n) {cout << 0; return 0;}
    for (int e : ans) cout << e << '\n';
    return 0;
}