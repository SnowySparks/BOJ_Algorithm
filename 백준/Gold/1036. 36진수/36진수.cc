#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#define f(a, b, c) for(int a=b;a<c;++a)
#define fr(a, b, c) for(int a=b;a>=c;--a)
using namespace std;
int n, k;
string st[50];
int char_to_num(char ch) {
    if (ch >= '0' && ch <= '9') return (int)ch - '0';
    else return ch - 'A' + 10;
}
char num_to_char(int val) {
    if (val < 10) return (char)( (int('0') + val));
    else return (char)( int('A') + val - 10);
}

struct info {
    int charnum;
    int w[52] = {0, };

    void sett() {
        f(i, 0, 51) {
            if (w[i] >= 36) {
                int q = w[i]/36;
                w[i] %= 36;
                w[i+1] += q;
            }
        }
    }
    void reset() {
        f(i, 0, 52) w[i] = 0;
    }

    bool operator>(const info &other) {
        fr(i, 51, 0) {
            if (w[i] != other.w[i]) return w[i] > other.w[i];
        }
        return charnum > other.charnum;
    }
};


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<info> alpha(36);
    cin >> n;
    f(i, 0, n) {
        cin >> st[i];
        reverse(st[i].begin(), st[i].end());
    }
    cin >> k;
    f(i, 0, 36) {alpha[i].charnum = i; alpha[i].reset();}

    f(i, 0, n) {
        int len = st[i].size();
        f(k, 0, len) {
            alpha[ char_to_num(st[i].at(k)) ].w[k] += (35 - char_to_num(st[i].at(k))); //z로 바꾸면 얻을 수 있는 이득치 계산
        }
    }
    f(i, 0, 36) {alpha[i].sett();}

    sort(alpha.begin(), alpha.end(), greater<>());
    //z변환할때 얻을 수 있는 이득치 중 가장 큰 것이 앞으로 오게끔
    unordered_set<char> z_list;
    if (k == 36) k--;
    f(i, 0, 36) {
        if (k == 0) break;
        if (alpha[i].charnum == 35) continue; //z는 굳이 할 필요가 없자나~
        z_list.insert(num_to_char(alpha[i].charnum));
        --k;
    }
    int w[54] = {0, };

    f(i, 0, n) {
        int len = st[i].size();
        f(k, 0, len) {
            char ch = st[i][k];
            if (z_list.find(ch) != z_list.end()) {
                w[k] += 35;
            }
            else w[k] += char_to_num(ch);
        }
    }

    f(i, 0, 53) {
        if (w[i] >= 36) {
            int q = w[i]/36;
            w[i] %= 36;
            w[i+1] += q;
        }        
    }

    string ans = "";
    f(i, 0, 54) ans.push_back(num_to_char(w[i]));
    while (true)
    {
        if (ans.empty() || ans.back() !='0') break;
        ans.pop_back();
    }
    if (ans.empty()) ans = "0";
    reverse(ans.begin(), ans.end());
    cout << ans;

    return 0;
}