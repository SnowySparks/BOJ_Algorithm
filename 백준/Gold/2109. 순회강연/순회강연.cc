#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
int n;

struct comp { //시간이 앞서는 순 동일하면 페이가 큰순
    bool operator() (const pii &a, const pii &b) const {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    }
};



int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    priority_queue< pii, vector<pii>, comp > pq; //데이터 삽입 - 시간순 그리고 페이 순
    //시간순인 이유 -> 그래야 차례적으로 페이 받을 수 있는 공간이 늘어나니까
    priority_queue< int, vector<int>, greater<> > r; //페이 담을 공간, -< 이크기가 곧 순회시간크기, 일부러 올림차순

    for (int i = 0 ; i < n ; ++i) {
        int p, d; cin >> p >> d;
        pq.push({p,d});
    }

    while (!pq.empty()) {
        while ( !r.empty() && r.size() >= pq.top().second && r.top() < pq.top().first ) r.pop();
        //만약에 현재 공연한 시간이 다음 받을 페이의 허용시간 이상인 경우
        //현재 가장 적은 페이들을 제거함. 단 받았던 페이들 중 가장 적은 페이값이
        //받을 페이값보다 큰 경우, 받았던 페이는 보존해야함
        if (r.size() < pq.top().second) r.push(pq.top().first);
        pq.pop();
    }

    int ans = 0;
    while(!r.empty()) {
        // cout <<"result : " <<r.top() <<'\n';
        ans+=r.top();
        r.pop();
    }
    cout << ans;
    return 0;
}