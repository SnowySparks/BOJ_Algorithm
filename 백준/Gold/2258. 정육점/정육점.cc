#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const ll inf = 1e15;
struct io {
    ll weight, cost;
};

io dt[100001];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m; cin >> n >> m;

// 가격 오름차순, 동일 가격에 대해선 무게 내림차순
    for (int i = 0; i < n; ++i) cin >> dt[i].weight >> dt[i].cost;
    sort(dt, dt+n, [](const io &a, const io &b) {
        if (a.cost == b.cost) return a.weight > b.weight;
        return a.cost < b.cost;
    });

    ll before_cost = -1; //직전 코스트 비용
    ll prefix_weight = 0; //  총 무게 합
    ll now_prefix_cost = 0; //현재 비용에서의 총 코스트
    ll ans = inf; //답
    for (int i = 0; i < n; ++i) {
        // 현재 코스트 != 직전 코스트 -> 현재 코스트로 갱신 및 현재 누적 코스트 초기화


        if (dt[i].cost != before_cost) {
            before_cost = dt[i].cost;
            now_prefix_cost = dt[i].cost;
        }
        else {
            // 현재 코스트 누적값 누적 갱신
            now_prefix_cost += dt[i].cost;
        }
        
        // 무게 갱신
        prefix_weight += dt[i].weight;

    // 현재 누적 무게가 m 이상인 경우, 정답 갱신
    // 이때 종료 안시키는 이유는 추후에 조금 더 높은 가격 하나를 사는 것이 이득이 될 수 있어서
    // ex : (1,3),(3,10),(3,2),(4,8)
        if (prefix_weight >= m) {
            ans = min(ans, now_prefix_cost);
        }
    }

    cout << (ans >= inf ? -1 : ans);

    return 0;
    
}