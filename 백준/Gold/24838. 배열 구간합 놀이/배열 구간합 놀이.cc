#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;
const long long dv = 1E9+7;
const int _max = 50002;

int xy[_max]; //구간 누적합 ( i ~ j 까지)
long long arr[_max]; //실제 데이터
int n, m; // n = 데이터 개수, m = 누적합 구간
unordered_map<int, long long> cntdt; // n개 개수가 몇 개?
long long pa[_max];
long long notzero;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    pa[0] = 1;
    for (int i = 1 ; i < _max ; i++) {
        pa[i] = pa[i-1] * i;
        pa[i] %= dv;
    }
    int T; cin >> T;
    int from, to;
    long long tcnt = 1; //최대 경우의 수
    long long maxadd = 0; //최대 누적 합
    while(T--) {
        cin >> n >> m;
        //데이터입력
        notzero = 0;
        fill(xy, xy+n+1,0);
        fill(arr,arr+1+n,0);
        for (int i = 1 ; i <= n ; i++) {
            cin >> arr[i];
        }
        //구간누적 입력
        for (int i = 1 ; i <= m ; i++) {
            cin >> from >> to;
            xy[from]++;
            xy[to+1]--;
        }
        tcnt = 1;
        //최종구간누적
        for (int i = 1 ; i <= n ; i++) {
            xy[i]+=xy[i-1];
            if (xy[i]) {cntdt[xy[i]]++; notzero++;}
        }

        for (auto e : cntdt) {
            tcnt *= pa[e.second];
            tcnt %= dv;
        }
        tcnt *=pa[ n - notzero];
        tcnt %= dv;

        sort( xy+1, xy+1+n, greater<>());
        sort( arr+1, arr+1+n, greater<>());
        maxadd = 0;
        for (int i = 1 ; i <= n ; i++) {
            if (xy[i] <= 0) break;
            maxadd += (xy[i] * arr[i]);
        }
        cout << maxadd << ' ' << tcnt << '\n';
        cntdt.clear();
    }
    return 0;
}