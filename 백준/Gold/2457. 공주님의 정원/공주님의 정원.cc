#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int month[] {0,31,28,31,30,31,30,31,31,30,31,30,31};
int toval(int m, int d) {
    return month[m-1]+d;
}
// 3m1d = 60 , 11m 30d = 334
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0);
    for (int i = 1 ; i <= 12 ; ++i) month[i]+=month[i-1]; //누~적합
    
    int n,m1,d1,m2,d2; cin >> n;
    vector<pii> dt;
    for (int i = 0 ; i < n; ++i) {
        cin >> m1 >> d1 >> m2 >> d2;
        int fr = toval(m1,d1); //맨 첨에 피는 날짜
        int en = toval(m2,d2); //지는 날짜
        if (en < toval(2,28)|| fr >= toval(12,1)) continue; // 3월 1일 보다 전 꽃이 지거나
        // 12월 1일 이후 피는 꽃은 애초에 대상이 안됨
        dt.push_back({fr,en});
    }
    sort(dt.begin(),dt.end()); //피는순서대로 배열

    int nowdate = toval(3,1), maxdate = 0, idx = 0 ,nidx = 0; //현재 꽃의 지는 날짜, 다음 꽃의 지는 날짜, 현재 꽃 인덱스 ,다음 꽃 인덱스
    //3월 1일보다 더 빠른 꽃을 찾는 것이 초기 값
    int ans = 0;

    while (nowdate < toval(12,1)) {
        // cout << '\n' <<idx <<"// nowdate : "<<nowdate << '\n';
        for (int i = idx ; i < dt.size(); ++i) {
            if (dt[i].first > nowdate) break; //현재 곧 지는 꽃의 날짜보다 더 늦게 꽃이 필 경우 -> 멈춤
            if (dt[i].second >= maxdate) { //가리킨 꽃이 마지막에 피는 날짜보다 현재 i 꽃이 더 뒤늦은 경우 데이터 갱신
                maxdate = dt[i].second;
                nidx = i;
            }
        }
        if (nowdate >= maxdate) { // 현재 꽃기 지기전 보다 다음 가장 뒤에 지는 꽃이 더 이르면 더이상 없다는 것
            ans=0;
            break;
        }
        else {
            nowdate = maxdate;
            idx = nidx;
            ++ans;
        }
    }
    cout << ans;
    return 0;
}