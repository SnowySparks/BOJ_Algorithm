#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define inf 100001
using namespace std;

int dt[21][21];
int dist[21][21];

void init(int N) {
    for (int i = 1 ; i <= N ; i++) {
        for (int j = 1 ; j <= N ; j++) {
            dist[i][j] = -1; } } }

typedef struct _info {
    int locr, locc, dr, dc; //손넘 행 열 위치 -> 손님 목적지 위치
} info;

int dr[] = {1,-1,0,0};
int dc[] = {0,0,1,-1};

vector<pair<int, info> > ppl;

void bfs(int nowr, int nowc, int N) {
    dist[nowr][nowc] = 0;
    queue<pair<int, pair<int ,int > > > q; //거리 좌표
    q.push({0,{nowr,nowc}});
    int cost, r, c , nextr, nextc;
    while (!q.empty()) {
        cost = q.front().first; r=q.front().second.first; c=q.front().second.second;
        q.pop();
        for (int i=0; i<4 ; i++) {
            nextr = r +dr[i]; nextc = c +dc[i];
            if (nextr >= 1 && nextc >=1 && nextr <= N && nextc <= N) {
                if (dt[nextr][nextc] != 1 && dist[nextr][nextc] == -1) {
                    dist[nextr][nextc] = cost + 1;
                    q.push({cost+1,{nextr,nextc}});
                }
            }
        }
    }
}

bool comp(const pair<int,info> &a,const pair<int,info> &b) {
    if (a.first == b.first) {
        if (a.second.locr == b.second.locr) {
            return a.second.locc < b.second.locc;
        }
        return a.second.locr < b.second.locr;
    } return a.first < b.first;
}

int main(void) {
    int N , people, fuel; cin >> N >> people >> fuel;
    for (int i = 1 ; i <= N ; i++) {
        for (int j = 1 ; j <= N ; j++) {
            cin >> dt[i][j];
        }
    }
    int car_r , car_c ; cin >> car_r >> car_c;
    int a,b,c,d;
    for (int i = 0 ; i < people ; i++) {
        cin >> a >> b >> c >> d ;
        ppl.push_back({0,{a,b,c,d}});
    }
    int done = 0;
    int cost;
    init(N);
    while (fuel > 0 && done < people) {
        bfs(car_r, car_c, N); //차가 손님 태우러 이동하는 것
        for (int i = done ; i < people; i++) {
            ppl[i].first = dist[ppl[i].second.locr][ppl[i].second.locc]; //거리측정
        }
        sort(ppl.begin() + done , ppl.end(),comp); //조건에 맞는 배열후 가장 앞에거 선택
        if (ppl[done].first < 0) {fuel = -1; break;} //애초에 못 태우는 손님존재 -> 즉각종료
        car_r = ppl[done].second.locr; car_c = ppl[done].second.locc; //차이동
        fuel -= ppl[done].first;
        if (fuel < 0) break; //연료 바닥이면 즉각종료
        init(N); //초기화 , 다시 이제 손님을 목적지로 태움
        bfs(car_r, car_c , N);
        cost = dist[ppl[done].second.dr][ppl[done].second.dc];
        if (cost < 0 ) {fuel = -1; break;} //목적지로 갈 수 없음 -> 종료
        fuel -= cost;
        if (fuel < 0) break; //연료바닥 -> 종료
        fuel += (2 * cost);
        car_r = ppl[done].second.dr; car_c=ppl[done].second.dc; //차 좌표 변경
        done++; //한 사람 처리했음을 의미.
        init(N);
    }

    if (fuel < 0) {cout << -1 ; return 0;}
    cout << fuel; return 0;
}