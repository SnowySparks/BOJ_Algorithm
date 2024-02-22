#include <iostream>
#include <vector>
#include <algorithm>
#define f(a, b, c) for(int a=b; a<c; ++a)
using namespace std;

struct info {
    int fr, to, box;
};

bool comp(const info &a, const info &b) {
    return a.to < b.to;
}
int truck_state[2001];


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, max_box;
    cin >> n >> max_box;
    int m; cin >> m;
    vector<info> dt(m);
    f(i, 0, m) cin >> dt[i].fr >> dt[i].to >> dt[i].box;
    //받은 위치 기준으로 오름차순 --> 이건 회의실 배정 문제와 유사한 이유
    sort(dt.begin(), dt.end(), comp);

    // a 부터 b까지 택배를 보내면 해당 거리 만큼 택배가 실어짐을 고려하기
    // 해당 거리에서 실어진 택배양중 최대값에서 허용량 만큼 뺀 것이 해당 업무에서 가능한 택배 수거 양
    //수거 하면 해당 거리에 추가적인 택배를 실었다는 표시를 해야함

    int ans = 0;
    for (info &work : dt) {
        int available = max_box; //가능한 박스 수거양
        int max_box_state = 0; // work.fr ~ work.to -1 까지 실어진 택배 총 양 어차피 도착점에는 박스를 다 내리기 때문에...
        f(i, work.fr, work.to) {
            max_box_state = max(max_box_state, truck_state[i] );
        }
        available = min(work.box, max_box - max_box_state);
        if (available) { //실어도 될 경우
            ans += available; //답 갱신
            f(i, work.fr, work.to) { 
                //해당 구간만큼 박스 실어 넣었다는 표시, 단 도착점은 어차피 박스를 내린다는 것에서 주의
                truck_state[i] += available;
            }
        }
    }
    cout << ans;
    return 0;
}