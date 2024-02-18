#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define BLUE 1
#define WHITE 2

vector<int> gh[101];
int n;
int color_state[101];
void bfs(int x) {
    color_state[x] = BLUE;
    queue<int> q;
    q.push(x);

    while (!q.empty()) {
        int loc = q.front(); q.pop();
        int ncolor = (color_state[loc] == BLUE ? WHITE : BLUE);

        for (int &child : gh[loc]) {
            if (!color_state[child]) {
                color_state[child] = ncolor;
                q.push(child);
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int tmp;
    cin >> n;
    for (int i = 1; i <=n; ++i) {
        int cnt; cin >> cnt;
        for (int k = 0; k < cnt; ++k) {
            cin >> tmp;
            gh[i].push_back(tmp);
            gh[tmp].push_back(i);
        }
    }

    for (int i = 1; i <=n; ++i) {
        if (color_state[i] == 0) bfs(i);
    }

    vector<int> b, w;
    for (int i = 1; i <= n; ++i) {
        if (color_state[i] == BLUE) b.push_back(i);
        else w.push_back(i);
    }

    cout <<(int)b.size() <<'\n';
    for (int &r : b) {
        cout << r << ' ';
    }
    cout <<'\n'<<(int)w.size() <<'\n';
    for (int &r : w) {
        cout << r << ' ';
    }
    return 0;
}