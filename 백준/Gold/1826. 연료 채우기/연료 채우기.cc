#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = 1e6+1;
const int mv = 1e8;
using pii = pair<int, int>;
int n;
pii arr[inf];

bool comp2(const pii &a , const pii &b) {
    return a.first < b.first;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);

    //input
    cin >> n;
    int village, fuel; //village 위치, 총합 fuel. -> fuel 총합이 곧 자동차가 이동 가능한 총 거리이기도 함
    for (int i = 0 ; i < n ; ++i) cin >> arr[i].first >> arr[i].second;
    sort(arr, arr+n); //주유소 위치 순 정렬
    cin >> village >> fuel;
    int cnt  = 0; //최소 주유 횟수
    int idx = 0;
    //그리디 관점 : 현재 갈 수 있는 주유소 중 가장 멀리 갈 수 있는 주유소만 가는 것이 이득
    //              단 다음 주유소를 갈 수 없는 경우. 이미 지나간 주유소 중 주유가능한 기름수가 많은 곳 순서대로 가능한 최소한 넣는것이 이득

    priority_queue<int> pq; //넣을 수 있는 주유소들 리스트 중 내림차순. 실제 넣는 것이아닌 대기영역
    while (village > fuel) {
        while(idx < n && fuel >= arr[idx].first )  {// 주유소 idx 가 범위 밖에 아니고, 주유소 가능한 것들 전부 대기시킴
            pq.push(arr[idx++].second);
        }
        if (pq.empty()) { //비어있는 경우 -> 더이상 다음 주유소에 못간다는 거고, village에 도착도 못함
            cnt = -1;
            break;
        }

        //안비어있는 경우 -> "한번만" 주유시켜보고 바로 다음 탐색 들어감
        ++cnt;
        fuel+=pq.top();
        pq.pop();
    }
    cout << cnt;
    return 0;
}