#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
using pii = pair<int, int>;
#define f(a,b,c) for(int a=b; a<c;++a)
int n;
 
bool v[100][100];
 
int dr[3] = {0,0,-1};
int dc[3] = {1,-1,0};
 
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    int T = 10,tmp;
    int sr, sc;
    for (int tc = 1 ; tc <= T ; ++tc) {
        //input
        cin >> tmp;
        f(i,0,100) {
            f(j,0,100) {
                cin >> tmp;
                if (tmp == 1) v[i][j] = false;
                else if (tmp==0) v[i][j] = true;
                else if (tmp==2) {
                    sr = i; sc = j;
                    v[i][j] = true;
                }
            }
        }
 
        int r= sr, c= sc;
        //simulation
        while(r>0) {
            f(i,0,3) {
                int nr = r + dr[i], nc = c+dc[i];
                if (nr < 0 || nr >= 100 || nc < 0 || nc >= 100 || v[nr][nc]) continue;
                r = nr; c = nc;
                v[nr][nc]=true;
                break;
            }
        }
        cout << '#' << tc <<' ' << c << '\n';
        memset(v,false,sizeof(v));
    }
    return 0;
}