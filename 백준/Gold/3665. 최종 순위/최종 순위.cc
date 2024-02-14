#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++)
int n, m;

int rk[501]; // rank , 인덱스 번호 = 팀, 값 : 등수
int lst[501]; // 인덱스 번호 : 등수, 값 : 팀번호
bool isswap[501][501];
int indegree[501];

vector<int> adj[501];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    f(tc, 1, T+1) {
        //초기화
        memset(isswap, 0, sizeof(isswap));
        memset(indegree, 0, sizeof(indegree));
        //입력
        cin >> n;
        f(i, 1, n+1) {
            cin >> lst[i];
            rk[ lst[i] ] = i;
        }
        cin >> m;
        //swap 정보 등록
        f(k, 0, m) {
            int a, b; cin >>a >> b;
            isswap[a][b] = true;
            isswap[b][a] = true;
        }

        //adj 정보 초기화
        f(i, 0, n+1) adj[i].clear();


        // 1등은 2등보다 우위이면서 3, 4, 5 ... 등보다도 우위이다
        // n^2 탐색을 전부 보면서 swap 관계까지 고려함
        f(i, 1, n) { //항상 lst[i] 순위가 lst[j]보다 높음. swap안한다면..
            f(j, i+1, n+1) {
                if (!isswap[lst[i]][lst[j]]) {
                    adj[lst[i]].push_back(lst[j]);
                    indegree[lst[j]]++;
                }
                else {
                    adj[lst[j]].push_back(lst[i]);
                    indegree[lst[i]]++;
                }
            }
        }
        queue<int> q;
        vector<int> ans;
        bool isquestion = false; //동일한 등수가 존재할 수 밖에 없는 경우
        f(i, 1, n+1) if (indegree[i] == 0) q.push(i);
        
        while (!q.empty()) {
            if ((int)q.size() > 1) {
                isquestion = true;
                break;
            }
            int loc = q.front(); q.pop();
            ans.push_back(loc);
            for (int nxt : adj[loc]) {
                --indegree[nxt];
                if (indegree[nxt] == 0) q.push(nxt);
            }
        }

        if (isquestion) cout << "?\n";
        else if ((int)ans.size() != n) cout << "IMPOSSIBLE\n"; //싸이클이 존재한다는 거임
        else {
            for (int a : ans) {
                cout << a << ' ';
            }
            cout <<'\n';
        }
    }
    return 0;
}