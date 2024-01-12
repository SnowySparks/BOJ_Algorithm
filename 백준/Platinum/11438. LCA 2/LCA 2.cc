#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int inf = 1E5+1;
using pii = pair<int,int>;
#define f(a,b,c) for(int a=b;a<=c;a++)
vector<int> adj[inf];
int parent[inf][18];
int level[inf];
int max_level;

void set_tree(int n, int p, int lv) {
    level[n] = lv;
    parent[n][0] = p;
    f(i,1,max_level) parent[n][i] = parent[parent[n][i-1]][i-1];
    for (auto e : adj[n]) {
        if ( e == p) continue;
        set_tree(e,n,lv+1);
    }
}

int lca(int a, int b) {
    //root node == 1 set
    if (a == 1 || b == 1) return 1;
    if (level[a] < level[b]) swap(a,b);

    int lvdiff = level[a] - level[b];
    for (int i = 0 ; lvdiff; i++) {
        if (lvdiff & 1) a = parent[a][i];
        lvdiff >>=1;
    }
    int ret = a;
    if (a != b) {
        for (int i = max_level; i >=0; i--) {
            if (parent[a][i]!=parent[b][i]){
                a = parent[a][i];
                b = parent[b][i];
            }
            ret = parent[a][i];
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    max_level = int(floor(log2(n)));
    f(i,0,n-2){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    set_tree(1,0,1);
    int m; cin >> m;
    int a, b;
    f(i,0,m-1) {
        cin >> a >> b;
        cout << lca(a,b) <<'\n';
    }
}