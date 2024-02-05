#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++)
using pii = pair<int,int>; 
using piii = pair<int , pii >; 
const int inf = 1e6;

int dt[7][7]; 
vector<pii> cord; //island coordinate list
vector<piii> island;
int gh[10][10]; // map data
bool v[10][10]; // visited map for bfs
int n,m; // max row and column
int cal = 0 ; // island lst
queue<pii> q; // bfs queue
int dr[] = {1, -1 , 0, 0};
int dc[] = {0, 0, 1, -1};

int p[7] = {0, 1, 2, 3, 4, 5, 6};

int parent(int a) {
    if (a == p[a]) return a;
    return p[a] = parent(p[a]);
}

bool unite(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return false;
    p[max(a,b)] = min(a,b);
    return true;
}


void bfs(int r, int c) {
    v[r][c] = true; q.push({r,c}); gh[r][c] = ++cal;
    while (!q.empty()) {
        int cr = q.front().first; int cc = q.front().second; q.pop();
        f(i,0,4) {
            int nr = cr + dr[i]; int nc = cc + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&!v[nr][nc] && gh[nr][nc]) {
                v[nr][nc] = true; q.push({nr,nc}); gh[nr][nc] = cal;
            }
        }
    }
}


void cal_distance(void) {
    int r, c, start, len = 0;
    for (pii loc : cord) { 
        f(i, 0, 4) {  
            start = gh[loc.first][loc.second];
            r = loc.first; c = loc.second; len = 0;
            while (1) {
                r += dr[i]; c += dc[i];
                if (r < 0 || r >= n || c < 0 || c >= m) break; 
                if (gh[r][c] == 0) len++; //bridge length ++
                else { 
                    if (len > 1 && gh[r][c] != start) { 
                        dt[gh[r][c]][start] = min(dt[gh[r][c]][start],len);
                        dt[start][gh[r][c]] = dt[gh[r][c]][start];
                    }
                    break;
                }
            }
        }
    }

    f(i,1,cal+1) f(k,i+1,cal+1) {
        if (dt[i][k] < inf) island.push_back({dt[i][k], {i,k}});
    }

    sort(island.begin(), island.end());
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n >> m;
    f(i,0,n) f(j,0,m) {cin >> gh[i][j]; if (gh[i][j]) cord.push_back({i,j});}

    f(i,0,n) f(j,0,m) {
        if (gh[i][j] && !v[i][j]) bfs(i,j);
        else v[i][j] = true;
    }

    f(i,0,7) f(j,0,7) dt[i][j] = inf;
    cal_distance();

    int ans = 0;

    // MST
    for (piii datas : island) {
        if (unite(datas.second.first,datas.second.second)) {
            ans+= datas.first;
        }
    }

    int sep = parent(1);
    f(i,2,cal+1) {
        if (parent(i)!=sep) {
            cout << -1;
            return 0;
        }
    }
    cout << ans;
    return 0;
}
