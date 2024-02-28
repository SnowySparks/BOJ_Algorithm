#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_map>
using namespace std;
int ans = 0;
int ab[10] = {0,};
int ten[6] = {100000, 10000, 1000, 100, 10, 1};
int swapnum(int num, int l, int r, int length) {
    int fix = 6 - length;
    int lnum = num % (ten[fix + l] * 10)/ ten[fix + l];
    int rnum = num % (ten[fix + r] * 10)/ ten[fix + r];
    num += lnum * (ten[fix + r] - ten[fix + l] );
    num += rnum * (ten[fix + l] - ten[fix + r] );

    return num;
}

bool issame(const string &a) {
    memset(ab,0,sizeof(ab));
    for (char ch : a) {
        ab[ ch - '0']++;
        if (ab[ch - '0'] % 2 == 0) return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    string a; int k;
    int len;
    unordered_map<int, int> v;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> a >> k;
        len = (int) a.size();
        ans = 0;
        v.clear();
        queue<int> q;
        q.push(stoi(a));
        bool same_num = issame(a);
        v[q.front()] = 0;
        while (!q.empty())
        {
            int now_num = q.front();
            q.pop();
            if (v[now_num] == k) continue;
            for (int i = 0; i < len-1; ++i) {
                for (int k = i+1; k < len; ++k) {
                    int nxt_num = swapnum(now_num, i, k, len);
                    if (v.find(nxt_num) == v.end()) {
                        v[nxt_num] = v[now_num] + 1;
                        q.push(nxt_num);
                    }
                }
            }
        }
        for (auto &[i, e] : v) {
            if ((k-e)%2 == 0 || same_num) ans = max(ans, i);
        }
        cout << '#' << tc << ' ' <<ans <<'\n';
    }
    return 0;
}