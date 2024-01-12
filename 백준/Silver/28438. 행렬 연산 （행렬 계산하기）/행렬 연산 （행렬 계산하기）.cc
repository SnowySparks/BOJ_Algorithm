#include <iostream>
using namespace std;
#define f(a,b,c) for(int a=b; a<=c;a++)
const int a = 5e5+1;
int row[a], col[a];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, q; cin >> n >> m >> q;
    int qr, loc, val;
    f(t,1,q) {
        cin >> qr >> loc >> val;
        if (qr == 1) row[loc]+=val;
        else col[loc]+=val;
    }

    f(i,1,n) {f(j,1,m) {cout << row[i]+col[j] << ' ';} cout <<'\n';}
    return 0;
}