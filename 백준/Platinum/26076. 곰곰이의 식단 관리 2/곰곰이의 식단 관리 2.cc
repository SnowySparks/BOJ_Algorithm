#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;
const int d = 1E5+1;
#define f(a,b,c) for(int a=b; a<c;a++) 

int n, m;
pair<int,int> mv[8] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int gh[2000][2000];
int cnt[2000][2000];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    memset(cnt,-1,sizeof(cnt));
    f(i,0,n) f(k,0,m) cin >> gh[i][k];
    deque<pair<int, int> > p;

    f(i,1,m) {
        if (gh[0][i]) {
            cnt[0][i] = 0; p.push_front({0,i});}
        else {
            cnt[0][i]= 1; p.push_back({0,i});}
    }

    f(i,1,n-1) {
        if (gh[i][m-1]) {cnt[i][m-1]=0; p.push_front({i,m-1});}
        else {cnt[i][m-1]= 1; p.push_back({i,m-1});}
    }

    while (!p.empty()) {
        int cr = p.front().first;
        int cc = p.front().second;
        p.pop_front();

        f(i,0,8) {
            int nr = cr + mv[i].first;
            int nc = cc + mv[i].second;

            if (nr>=0 && nc>=0 && nr < n && nc < m) {
                if (cnt[nr][nc] == -1 && gh[nr][nc]==0) {
                    cnt[nr][nc] = cnt[cr][cc]+1;
                    p.push_back({nr,nc});
                }
                else if (cnt[nr][nc]==-1 && gh[nr][nc]==1) {
                    cnt[nr][nc]= cnt[cr][cc];
                    p.push_front({nr,nc});
                }
            }
        }
    }

    int ans = 2;

    if (n>1) f(i,1,n-1) ans = min(ans,cnt[i][0]);
    if (m>1) f(i,1,m-1) ans = min(ans,cnt[n-1][i]);
    if (n>1 && m>1) ans = min(ans,cnt[n-1][0]);
    cout << ans;
    return 0;
}