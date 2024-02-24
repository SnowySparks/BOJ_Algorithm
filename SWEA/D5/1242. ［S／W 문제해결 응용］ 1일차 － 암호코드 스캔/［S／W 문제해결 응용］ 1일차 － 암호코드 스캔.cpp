#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)

int n, m;
unordered_set<string> used_code;

//코드 길이 비, 순서대로 1, 0, 1의 길이
//가장 맨앞 0은 어차피 생각해보니 굳이... 탐색 할 필요가 없었네? 어
int code_lst[5][5][5];
int input_bincode[8];
int hex_to_bin[16][4] {
    {0, 0, 0, 0}, //0
    {0, 0, 0, 1}, //1
    {0, 0, 1, 0}, //2
    {0, 0, 1, 1}, //3
    {0, 1, 0, 0}, //4
    {0, 1, 0, 1}, //5
    {0, 1, 1, 0}, //6
    {0, 1, 1, 1}, //7
    {1, 0, 0, 0}, //8
    {1, 0, 0, 1}, //9
    {1, 0, 1, 0}, //A
    {1, 0, 1, 1}, //B
    {1, 1, 0, 0}, //C
    {1, 1, 0, 1}, //D
    {1, 1, 1, 0}, //E
    {1, 1, 1, 1}, //F
};

short bin[2000][2000];

int hex_to_ten(const char &ch) {
    if (ch >='0' && ch <= '9') return ch - '0';
    else return ch - 'A' + 10;
}

int correct_code(void) {
    int r1 = input_bincode[0] + input_bincode[2] + input_bincode[4] + input_bincode[6];
    int r2 = input_bincode[1] + input_bincode[3] + input_bincode[5];
    int r3 = input_bincode[7];
    if ((r1*3 + r2 + r3) %10 == 0) return r1 + r2 + r3;
    return 0;
}

int check_code(int r) {
    int res = 0;
    int n3 = 0, n2 = 0, n1 = 0;
    int idx = 4*m -1;
    int ans_idx = 7;
    while (idx >= 0) {
        if (bin[r][idx] == 1 &&bin[r-1][idx] == 0 ) {
            n3 = 0; n2 = 0; n1 = 0;
            while (bin[r][idx] == 1) {++n3; --idx;}
            while (bin[r][idx] == 0) {++n2; --idx;}
            while (bin[r][idx] == 1) {++n1; --idx;}
            ++idx;

            int min_val = min(n3, min(n2, n1));
            n3 /= min_val;
            n2 /= min_val;
            n1 /= min_val;
            
            int code_r = code_lst[n1][n2][n3];
            if (code_r == -1) {
                ans_idx = 7;
            }
            else {
                input_bincode[ans_idx--] = code_r;
                if (ans_idx == -1) {
                    res += correct_code();
                    ans_idx = 7;
                }
            }
        }
        --idx;
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    f(i, 0, 5) f(j, 0, 5) f(k, 0, 5) code_lst[i][j][k] = -1;
    code_lst[2][1][1] = 0;
    code_lst[2][2][1] = 1;
    code_lst[1][2][2] = 2;
    code_lst[4][1][1] = 3;
    code_lst[1][3][2] = 4;
    code_lst[2][3][1] = 5;
    code_lst[1][1][4] = 6;
    code_lst[3][1][2] = 7;
    code_lst[2][1][3] = 8;
    code_lst[1][1][2] = 9;
    // freopen("input.txt","r",stdin);


    int T; cin >> T;
    string inp;
    f(tc, 1, T + 1) {
        int ans = 0;
        cin >> n >> m;
        f(r, 0, n) {
            cin >> inp;
            f(c, 0, m) {
                for (int idx = 4*c; idx < (4*(c+1)) ; ++idx) {
                    bin[r][idx] = hex_to_bin[hex_to_ten(inp[c])][idx - 4*c];
                }
            }
        }
        f(r, 1, n) ans +=check_code(r);
        cout << '#' <<tc <<' '<<ans <<'\n';
    }
    return 0;
}