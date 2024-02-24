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
unordered_map<string, char> codelst = {
    {"211", '0'},
    {"221", '1'},
    {"122", '2'},
    {"411", '3'},
    {"132", '4'},
    {"231", '5'},
    {"114", '6'},
    {"312", '7'},
    {"213", '8'},
    {"112", '9'},
};

unordered_map<char, string> hex_to_bin {
    {'0',"0000"},
    {'1',"0001"},
    {'2',"0010"},
    {'3',"0011"},
    {'4',"0100"},
    {'5',"0101"},
    {'6',"0110"},
    {'7',"0111"},
    {'8',"1000"},
    {'9',"1001"},
    {'A',"1010"},
    {'B',"1011"},
    {'C',"1100"},
    {'D',"1101"},
    {'E',"1110"},
    {'F',"1111"},
};


int correct_code (const string &code) {
    if ((int)code.size() != 8 ) return 0;
    int r1 = 0, r2 = 0, r3 = code[7] - '0';
    for (int i = 0; i <= 6; i+=2) r1 += (code[i] - '0');
    for (int i = 1; i <7; i+=2) r2 += (code[i] - '0');
    if ((r1*3 + r2 + r3)%10==0) return r1 + r2 + r3;
    else return 0;

}

int check_code(const string &bin) {
    int res = 0;
    int n3 = 0, n2 = 0, n1 = 0;
    int idx = 4*m -1;
    string complete_code = "";
    while (idx >= 0) {
        if (bin[idx] == '1') {
            n3 = 0; n2 = 0; n1 = 0;
            while (bin[idx] == '1') {++n3; --idx;}
            while (bin[idx] == '0') {++n2; --idx;}
            while (bin[idx] == '1') {++n1; --idx;}
            ++idx;

            int min_val = min(n3, min(n2, n1));
            n3 /= min_val;
            n2 /= min_val;
            n1 /= min_val;
            
            string c1 = to_string(100 *n1 + 10*n2 + n3);
            if (codelst.find(c1) == codelst.end()) {
                complete_code.clear();
            }
            else {
                complete_code.push_back(codelst[c1]);
                if ((int)complete_code.size() == 8) {
                    if (used_code.find(complete_code) == used_code.end()) {
                        used_code.insert(complete_code);
                        // cout << complete_code << '\n';
                        reverse(complete_code.begin(), complete_code.end());
                        res += correct_code(complete_code);
                    }
                    complete_code.clear();
                }
            }
        }
        --idx;
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    string inp;
    f(tc, 1, T + 1) {
        int ans = 0;
        cin >> n >> m;
        used_code.clear();
        f(r, 0, n) {
            string binary = "";
            cin >> inp;
            //이진수 변환
            for (char hex : inp) {
                binary += hex_to_bin[hex];
            }
            //가장 뒤에서 부터 탐색
            ans += check_code(binary);
        }
        cout << '#' <<tc <<' '<<ans <<'\n';
    }
    return 0;
}