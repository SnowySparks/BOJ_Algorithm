#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <cstring>
using namespace std;
using pii = pair<int, int>;
int n;
const int inf = 1e5+1;
int height[inf]; // height with input idx i
int ed[inf]; // end_point with (input idx i)

struct io {
    int x, i, state; //좌표, idx, (시작 == 0 or 종료 == 1)
};

int now_height = 0;

vector<io> arr; // (시작점, 입력인덱스, 시작 or 종료)
vector<pii> ans; // (답)
priority_queue<pii> pq; // (-높이, 끝점위치)
unordered_set<int> end_lst; // 끝점 리스트 (살펴본 끝점 위치) 저장

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    int l, h, r;
    for (int i = 0; i < n; ++i) {
        cin >> l >> h >> r;
        height[i] = h;
        ed[i] = r;
        arr.push_back({l, i, 0});
        arr.push_back({r, i, 1});
    }

    sort(arr.begin(), arr.end(), [](const io &a, const io &b) {
        // 1순위 x좌표 오름차순
        // 2 순위 . 시작 > 종료
        // 3 순위 높이 내림차순
        if (a.x != b.x) return a.x < b.x;
        if (a.state != b.state) return a.state < b.state;
        return height[a.i] > height[b.i];
    });

    for (auto &[x, i, state] : arr) {
        // cout << x <<' ' << height[i] <<' ' << state << '\n';
        if (!state) { //건물 시작점
            if (now_height < height[i]) { // 더 높은 건물 -> 갱신 및 답 추가
                ans.push_back({x, height[i]}); // 
                now_height = height[i];
            }
            pq.push({height[i], ed[i]}); // 일단 끝점 추가
        }
        else {
            end_lst.insert(x); //일단 끝점리스트 추가
            // 현재 높이 우선순위에 따른 끝점 정보에서 해당 끝점이 끝점 정보에 저장되어 있으면 아닐 때 까지 제거
            if (pq.empty()) continue; //단 이미 빈 상태면 스킵
            while (!pq.empty() && end_lst.find(pq.top().second) != end_lst.end() ) pq.pop();

            // 빈 경우 -> 바닥
            if (pq.empty()) {
                now_height = 0;
                ans.push_back({x, 0});
            }
            //아닌경우
            else {

                if (now_height != pq.top().first) {
                    now_height = pq.top().first;
                    ans.push_back({x, now_height});
                }
            }
        }
        // cout << x <<' ' << now_height << '\n';
    }

    for (pii d : ans) {
        cout << d.first <<' ' <<d.second <<' ';
    }




    return 0;
}