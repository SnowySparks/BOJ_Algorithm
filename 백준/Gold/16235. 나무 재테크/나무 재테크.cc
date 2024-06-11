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

int trees[10][10][10000];
int ts[10][10]; //tree_size number
int tmp[10][10]; // 

// vector<pii > trees[10][10]; //vectors; <tree age, tree alive>

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
        trees[r][c][ts[r][c]++] = z;
    }

    while (k--)
    {
        //양분먹기
        memset(tmp, 0, sizeof(tmp));
        f(i, 0, n) f(j, 0, n) {
            sort(trees[i][j],  trees[i][j]+ts[i][j]); 
            f(p, 0, ts[i][j]) {
                if (trees[i][j][p] <= nur[i][j]) {
                    nur[i][j] -= trees[i][j][p];
                    trees[i][j][p]++;
                    tmp[i][j]++;
                }
                else break;
            }
        }

        //여름 - 즉은 나무 양분화
        f(i, 0, n) f(j, 0, n) {
            int cnt = ts[i][j] - tmp[i][j];
            for (int p = tmp[i][j]; p < ts[i][j]; ++p) {
                nur[i][j] += (trees[i][j][p]/2);
            }
            ts[i][j]-=cnt;
        }

        
        //가을 - 번식
        f(i, 0, n) f(j, 0, n) {
            f(p, 0, ts[i][j]) {
                if (trees[i][j][p]%5==0) {
                    for (auto &[dr, dc] : mv) {
                        int nr = i +dr, nc = j + dc;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                        trees[nr][nc][ts[nr][nc]++] = 1;
                    }
                }
            }
        }

        //겨울
        f(i, 0, n) f(j, 0, n) nur[i][j] += arr[i][j];
        // f(i, 0, n) {
        //     f(j, 0, n) cout << ts[i][j] <<' ';
        //     cout << '\n';
        // }
        // cout<< "-------\n";
    }

    int ans = 0;
    f(i, 0, n) f(j,0,n) ans += ts[i][j];
    cout << ans;
}