#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++)
using pii = pair<int,int>; 
const int inf = 1e6;

pii operator+(const pii &a, const pii &b) { return {a.first+b.first, a.second+b.second}; }
int m, n;
bool v[10][10][10][10]; // blue (row, column) and red (row, column) visit check
string inp[10]; // map info

typedef struct _info {
    pii red, blue; int cnt;
} io;

pii mv[4] = {{0,1},{1,0},{-1,0},{0,-1}};

pii move(pii cur, const pii &other ,int dir) { //움직일 것, 다른 거, 방향
    pii cnt = cur;
    while (true) {
        pii nxt = cnt + mv[dir];
        char ch = inp[nxt.first][nxt.second];
        if (nxt == other && ch!='O') {break;} // other ball exist - no more move with that diretion .
        else if (ch == '.') {cnt = nxt; continue;} //empty - keep going
        else if (ch == 'O') {cnt = nxt; break;} // hole - end
        else {break;} // somthing block, # or other color
    }
    return cnt;
}

pair<pii,pii> simulation(pii red, pii blue, int dir) { //기울일 때 시물레이션 코드
    pii nred = {0,0}, nblue = {0,0};
    if (dir == 0) {
        if (red.second > blue.second) {
            nred = move(red, blue, dir);
            nblue = move(blue, nred, dir);
        }
        else {
            nblue = move(blue, red, dir);
            nred = move(red, nblue, dir);
        }
    }
    else if (dir == 3) {
        if (red.second < blue.second) {
            nred = move(red, blue, dir);
            nblue = move(blue, nred, dir);
        }
        else {
            nblue = move(blue, red, dir);
            nred = move(red, nblue, dir);
        }        
    }
    else if (dir == 1) {
        if (red.first > blue.first) {
            nred = move(red, blue, dir);
            nblue = move(blue, nred, dir);
        }
        else {
            nblue = move(blue, red, dir);
            nred = move(red, nblue, dir);
        }         
    }
    else {
        if (red.first < blue.first) {
            nred = move(red, blue, dir);
            nblue = move(blue, nred, dir);
        }
        else {
            nblue = move(blue, red, dir);
            nred = move(red, nblue, dir);
        }         
    }
    return {nred, nblue};
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    pii first_red, first_blue, hole;
    f(i,0,n) {
        cin >> inp[i];
        f(j,0,m) {
            if (inp[i][j] == 'R') {first_red = {i,j}; inp[i][j] = '.';}
            if (inp[i][j] == 'B') {first_blue = {i,j}; inp[i][j] = '.';}
            if (inp[i][j] == 'O') hole = {i,j};
        }
    }
    queue<io> q;
    q.push({first_red, first_blue, 0});
    v[first_red.first][first_red.second][first_blue.first][first_blue.second] = true;
    int ans = -1;

    while (!q.empty()) {
        io cur = q.front(); q.pop();
        if (cur.cnt <= 10 && cur.red == hole && cur.blue != hole) { //red out and blue not out
            ans = cur.cnt;
            break;
        }
        else if (cur.cnt <= 10 && cur.blue == hole) { //blue out --> no more using data
            continue;
        }
        else if (cur.cnt >= 10) continue; // max allow is 10.
        for (int i=0; i<4; i++) {
            pair<pii,pii> nxt = simulation(cur.red, cur.blue, i);
            if (!v[nxt.first.first][nxt.first.second][nxt.second.first][nxt.second.second]) {
                v[nxt.first.first][nxt.first.second][nxt.second.first][nxt.second.second] = true;
                q.push({nxt.first,nxt.second, cur.cnt+1});
            }
        }

    }
    cout << ans;
    return 0;

}