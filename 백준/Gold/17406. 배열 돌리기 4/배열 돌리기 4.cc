#include <iostream>
#include <vector>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;++a)
int n, m, k;
int arr[50][50], temp[50][50], rotate[50][50];

void rot(int r, int c, int s) {
    int tmp[4];
    f(rng, 1, s+1) {
        int min_r = r-rng, min_c = c-rng;
        int max_r = r+rng, max_c = c + rng;
        
        //가장자리 보존
        tmp[0] = arr[min_r][min_c]; 
        tmp[1] = arr[min_r][max_c];
        tmp[2] = arr[max_r][max_c];
        tmp[3] = arr[max_r][min_c];

        //윗변 이동
        for (int col = max_c-1; col > min_c; --col) {
            arr[min_r][col+1] = arr[min_r][col];
        }
        //우변 이동
        for (int row = max_r-1; row > min_r; --row) {
            arr[row+1][max_c] = arr[row][max_c];
        }
        //아랫변이동
        for (int col = min_c+1; col < max_c ; ++col) {
            arr[max_r][col-1] = arr[max_r][col];
        }
        //좌변 이동
        for (int row = min_r+1; row < max_r ; ++row) {
            arr[row -1][min_c] = arr[row][min_c];
        }

        //가장자리 원복
        arr[min_r][min_c+1] = tmp[0];
        arr[min_r+1][max_c] = tmp[1];
        arr[max_r][max_c-1] = tmp[2];
        arr[max_r-1][min_c] = tmp[3];
    }
}

//반시계방향이동
void rotccw(int r, int c, int s) {
    int tmp[4];
    f(rng, 1, s+1) {
        int min_r = r-rng, min_c = c-rng;
        int max_r = r+rng, max_c = c + rng;
        
        //가장자리 보존
        tmp[0] = arr[min_r][min_c]; 
        tmp[1] = arr[min_r][max_c];
        tmp[2] = arr[max_r][max_c];
        tmp[3] = arr[max_r][min_c];

        //윗변 이동
        for (int col = min_c+1; col < max_c; ++col) {
            arr[min_r][col-1] = arr[min_r][col];
        }
        //우변 이동
        for (int row = min_r+1; row < max_r; ++row) {
            arr[row-1][max_c] = arr[row][max_c];
        }
        //아랫변이동
        for (int col = max_c-1; col > min_c ; --col) {
            arr[max_r][col+1] = arr[max_r][col];
        }
        //좌변 이동
        for (int row = max_r-1; row > min_r ; --row) {
            arr[row +1][min_c] = arr[row][min_c];
        }

        //가장자리 원복
        arr[min_r+1][min_c] = tmp[0];
        arr[min_r][max_c-1] = tmp[1];
        arr[max_r-1][max_c] = tmp[2];
        arr[max_r][min_c+1] = tmp[3];
    }
}


int min_sum() {
    int ans = 1e5;
    f(row,0,n) {
        int cnt = 0;
        f(col,0,m) cnt+= arr[row][col];
        ans = min(ans,cnt);
    }
    return ans;
}

// void pnt() {
//     f(i,0,n) {
//         f(j,0,m) cout << arr[i][j] <<' ';
//         cout << '\n';
//     }
// }

typedef struct ROTINFO {
    int r, c, s;
}rtio;

//backstracking
vector<rtio> lst;

bool v[6];
int ans = 1e6;

void backtracking(int cnt) {
    if (cnt == k) {
        ans = min(ans, min_sum());
        return;
    }
    for (int i = 0 ; i < k ; ++i) {
        if (v[i]) continue;
        v[i]=true;
        rot(lst[i].r,lst[i].c,lst[i].s);
        backtracking(cnt+1);
        rotccw(lst[i].r,lst[i].c,lst[i].s);
        v[i]=false;
    }

}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    f(i,0,n) f(j,0,m) cin >> arr[i][j];
    lst.resize(k);
    f(i,0,k) {
        cin >> lst[i].r >> lst[i].c >> lst[i].s;
        lst[i].r--; lst[i].c--;
    }
    backtracking(0);
    cout << ans;

    return 0;
}