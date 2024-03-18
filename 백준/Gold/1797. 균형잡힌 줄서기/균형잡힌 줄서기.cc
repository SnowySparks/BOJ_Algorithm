#include <iostream>
#include <vector>
#include <algorithm>
#define _s1 (int)1E6
#define _s2 (int)2E6+2
using namespace std;

int first_exist[_s2];
//누적합 값 0 == 위치 1백만 , 저장값 : 실제 그 인덱스 위치
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<pair< int, int > > dt(N+1);
    int answer = 0;
    int np = 0;
    fill(first_exist, first_exist+_s2, -1);
    first_exist[_s1] = 0;
    for (int i =1 ; i <= N ; i++) { cin >> dt[i].second >> dt[i].first; }
    sort(dt.begin()+1,dt.end());
    for (int i = 1 ; i <= N ;i++) {
        np = np + (dt[i].second ? 1 : -1);
        if (first_exist[_s1 + np] == -1) first_exist[_s1 + np] = i;
        else {
            answer = max ( answer, dt[i].first - dt[ first_exist[ np+ _s1] +1 ].first);
        }
    }
    cout << answer;
    return 0;
}