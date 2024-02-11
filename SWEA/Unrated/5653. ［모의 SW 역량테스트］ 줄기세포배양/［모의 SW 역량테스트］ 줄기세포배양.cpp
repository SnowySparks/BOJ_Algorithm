#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<deque>
#define f(a,b,c) for(int a= b; a<c; ++a)
#define BASE 170
using namespace std;

int dr[] {1, -1, 0, 0};
int dc[] {0, 0, 1, -1};

struct info {
    int r, c, stime, dur; //행, 열, 번식 시작, 지속시간
    bool operator<(const struct info &a) const {
        return dur < a.dur;
    }
    bool operator>(const struct info &a) const {
        return dur > a.dur;
    }
};

int N, M, K;
int t;
int gh[400][400];
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T;
	// freopen("input.txt", "r", stdin);
    deque<info> dq;
    vector<info> temp_case;
	cin>>T;
	for(int test_case = 1; test_case <= T; ++test_case) {
        //reset
        memset(gh, 0, sizeof(gh));
        dq.clear();
        temp_case.clear();
        t = 0;
        //input
        cin >> N >> M >> K;
        //현재 줄기가 생성되었을 때(t), 생성되어지고 있는 시간은 t+d 이상 t + 2d미만임
        f(i,BASE,N+BASE) {
            f(j, BASE, M+BASE) {
                cin >> gh[i][j];
                if (gh[i][j]) {
                    temp_case.push_back({i, j, gh[i][j] + t, gh[i][j]});
                }
            }
        }
        // 생명력 높은 것부터 우선적으로 탐색
        sort(temp_case.begin(), temp_case.end());
        //역순으로 탐색
        for (auto it = temp_case.rbegin(); it != temp_case.rend(); it++) {
            dq.push_back(*it);
        }
        //simulation
        while(t < K) {
            int con = (int) dq.size();
            f(i, 0, con) {
                info dt = dq.front(); dq.pop_front();
                //아직 생성 시작 전
                if (dt.stime > t) {
                    dq.push_back(dt);
                }
                //생성 시간 대 안
                else if (dt.stime + dt.dur > t) {
                    f(k, 0 , 4) {
                        int nr = dt.r + dr[k], nc = dt.c + dc[k];
                        if (nr < 0 || nc < 0 || nr >=400 || nc >= 400 || gh[nr][nc]) continue;
                        gh[nr][nc] = dt.dur;
                        dq.push_back({nr, nc, t + dt.dur+1, dt.dur});
                    }

                    //다음 시간에도 활용 가능할 경우. 재등록
                    if (dt.stime + dt.dur - t > 1) dq.push_back(dt);
                }
                //이후는 생각할 필요도 없음
            }
            ++t;
        }
        cout << '#' << test_case << ' ' << (int)dq.size() << '\n';
	}
	return 0;
}