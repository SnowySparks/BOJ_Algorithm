#include <iostream>
#include <vector>
#include <algorithm>
#define inf 987654321
using namespace std;

vector<pair<int,int> > house;
vector<pair<int, int> > chicken_house;
vector<bool> visited;

//멘해튼 거리
int dist(const pair<int,int> &a1, const pair<int,int> &a2) {
    return abs(a1.first - a2.first) + abs(a1.second - a2.second);
}

//M 개의 치킨집을 남길 때 가장 최소의 치킨 거리
int sum = 0, tp, result = inf;
void back_track(int cnt, int idx, int n, int m) {
    if (cnt == m) { //조합 구했을 때, 도시치킨거리구하기
        sum = 0;
        for (auto e : house) {
            tp = inf;
            for (int i = 0 ; i < visited.size() ; i++) {
                if (visited[i]) {
                    tp = min(tp, dist(e,chicken_house[i]));
                }  
            }
            sum += tp;
        }
        result = min (result, sum);
    }
    else {
        for (int i = idx ; i < n ; i++) {
            if (visited[i]) continue;
            visited[i] = true;
            back_track(cnt+1,i+1,n,m);
            visited[i] = false;
        }
    }
    
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N,M; cin >> N >> M; 
    int temp;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> temp;
            if (temp == 2) {chicken_house.push_back({i,j}); visited.push_back(false);}
            else if ( temp == 1) house.push_back({i,j});
        }
    }
    int ans = inf;
    
    for (int i = 1 ; i <= M ; i++) {
        result = inf;
        back_track(0,0,chicken_house.size(),i);
        ans = min (ans , result);
    }
    cout << ans;
    return 0;
}