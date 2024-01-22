#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define INF 100000000
int maps[20][20];
int dist[20][20];

int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};

int now_size = 2; //아기상어 size
int now_r=0,now_c=0; //아기상어 현재 위치 

void bfs(int N) { //아기 상어 자체 크기 고려해서 갈 수 있는 곳의 거리 측정
    //거리 초기화
    for (int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j <N; j++) {dist[i][j] = -1;}
    }
    dist[now_r][now_c] = 0;
    queue<pair<int, int> > q;
    q.push({now_r,now_c});
    int r,c,nr,nc;
    while (!q.empty()) {
        r= q.front().first ; c = q.front().second;
        q.pop();
        for (int i = 0 ; i < 4 ; i++) {
            nr = r + dr[i]; nc = c +dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                if (dist[nr][nc]== -1 && maps[nr][nc] <= now_size) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr,nc});
                }
            }
        }
    }
}

vector<int> save(3);
void find_dist( int N ) {
    int min_dist = INF;
    int next_r, next_c;
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0; j < N ; j++) {
            if (dist[i][j] != -1 && maps[i][j] < now_size && maps[i][j] > 0) {
                if (min_dist > dist[i][j]) {
                    min_dist = dist[i][j];
                    next_r = i; next_c = j;
                }
            }
        }
    }
    save[0] = min_dist; save[1] = next_r; save[2] = next_c;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N; cin >> N;

    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < N ; j++) {
            cin >> maps[i][j];
            if (maps[i][j] == 9) {
                now_r = i; now_c = j;
                maps[i][j] = 0;
            }
        }
    }
    int ans = 0;
    int count = 0;
    while (true) {
        bfs(N);
        find_dist(N);
        if (save[0] == INF) break;
        else {
            now_r = save[1]; now_c = save[2];
            maps[now_r][now_c] = 0;
            ans+=save[0];
            count++;
            if (count >= now_size) {now_size++; count = 0;}
        }
    }
    cout << ans;
    return 0;

}