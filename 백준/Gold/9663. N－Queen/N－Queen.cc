#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int col[15]; // col[i]  == (col[i] , i)
int total = 0;

bool isdialogal(int level) {
    for (int i = 0 ; i < level ; i++) {
        //같은 행에 있거나, 대각선 위치에 있을 경우는 제외 ( 행 차이 크기 == 열 차이 크기 -> 대각선)
        if (col[i] == col[level] || abs(col[level] - col[i]) == level - i) {
            return false;    
        }
    }
    return true;
}

void dfs(int x, int N) { // x번째 배치 , 최대 N개
    if (x == N) {total++; return;}
    for (int i = 0 ; i < N; i++) {
        //x 열에 일단 배치를 하고, 검사를 해서 맞는 조건인 경우 dfs시행
        col[x] = i;
        if (isdialogal(x)) {dfs(x+1,N);}
    }
}

int main(void) {
    int N ; cin >> N;
    dfs(0,N);
    cout << total;
    return 0;
}