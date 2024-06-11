#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
int n, m, k;
int arr[10][10];
int nur[10][10];
using pii = pair<int, int>;
vector<pii > trees[10][10]; //vectors; <tree age, tree alive>

int mv[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    f(i, 0, n) f(j, 0, n) {
        cin >> arr[i][j];
        nur[i][j] = 5;
    }
    f(i, 0, m) {
        int r, c, z;
        cin >> r >> c >> z;
        r--; c--;
        trees[r][c].push_back({z,1});
    }

    while (k--)
    {
        //양분먹기
        f(i, 0, n) f(j, 0, n) {
            sort(trees[i][j].begin(),  trees[i][j].end()); 
            for (pii &tree : trees[i][j]) {
                if (nur[i][j] >= tree.first) {
                    nur[i][j] -= tree.first;
                    tree.first+=1;
                }
                else {
                    tree.second = 0;
                }
            }
        }

        //여름 - 즉은 나무 양분화
        f(i, 0, n) f(j, 0, n) {
            while (!trees[i][j].empty() && trees[i][j].back().second == 0)
            {
                nur[i][j] += (trees[i][j].back().first / 2);
                trees[i][j].pop_back();
            }
        }

        //가을 - 번식
        f(i, 0, n) f(j, 0, n) {
            for (pii &tree : trees[i][j]) {
                if (tree.first % 5 == 0) {
                    for (auto &[dr, dc] : mv) {
                        int nr = i +dr, nc = j + dc;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                        trees[nr][nc].push_back({1, 1});
                    }
                }
            }
        }

        //겨울
        f(i, 0, n) f(j, 0, n) nur[i][j] += arr[i][j];
    }

    int ans = 0;
    f(i, 0, n) f(j,0,n) ans += (int) trees[i][j].size();
    cout << ans;
}