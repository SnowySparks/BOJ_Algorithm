#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#define f(a,b,c) for(int a=b;a<c;a++)

using namespace std;
int n;

int dr[] {0,0,1,-1};
int dc[] {1,-1,0,0};

int visited[50][50];
string inp[50];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i,0,n) cin >> inp[i];
    memset(visited,-1,sizeof(visited));
    deque<pair<int, int> >  q;
    q.push_back({0,0}); visited[0][0] = 0;

    while (!q.empty()) {
        pair<int,int> loc = q.front(); q.pop_front();
        if (loc.first == n-1 && loc.second == n-1) break;
        f(i,0,4) {
            int nr = loc.first + dr[i];
            int nc = loc.second + dc[i];

            if (nr >= 0 && nc >= 0 && nr < n && nc < n) {
                if (inp[nr][nc] == '1' && visited[nr][nc] == -1) {
                    q.push_front({nr,nc});
                    visited[nr][nc] = visited[loc.first][loc.second];
                }
                else if (inp[nr][nc] == '0' && visited[nr][nc] == -1) {
                    q.push_back({nr,nc});
                    visited[nr][nc] = visited[loc.first][loc.second]+1;
                }
            }
        }
    }
    cout << visited[n-1][n-1];
    return 0;
}

