#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

string input[9];

bool isright(int r, int c) {
    for (int i = 0; i < 9; i++) {
        if (r!=i && input[i][c] == input[r][c]) return false;
        if (c!=i && input[r][i] == input[r][c]) return false;
    }
    for (int i = r/3*3 ; i < r/3*3+3 ; i++) {
        for (int j = c/3*3; j < c/3*3+3 ; j++) {
            if (!(i==r && j==c)) {
                if (input[i][j] == input[r][c]) return false;
            }
        }
    }
    return true;
}

vector<pair<int, int> > zerolocations;
bool isfound = false;
char num[] = {'1','2','3','4','5','6','7','8','9'};
void back_tracking (int idx) {
    if (isfound) return;
    if (idx == zerolocations.size()) {
        for (int i = 0; i < 9 ; i++) {
            cout << input[i] <<'\n';
        }
        isfound = true;
        return;
    }

    int lr = zerolocations[idx].first;
    int lc = zerolocations[idx].second;
    for (int i = 0; i < 9 ; i++) {
        input[lr][lc] = num[i];
        if (isright(lr,lc)) back_tracking(idx+1);
        if (isfound) return;  
    }
    input[lr][lc] = '0'; return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    for (int i = 0; i < 9 ; i++) {
        cin >> input[i]; 
        for (int j = 0; j < 9 ; j++) {
            if (input[i][j] == '0') zerolocations.push_back({i,j});
        }
    }
    back_tracking(0);
    return 0;
}