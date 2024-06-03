#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
using namespace std;
const int inf = 40000;
const int p = 27;
const int mod = 1000003; // 소수
vector<int> prime;
bool sz[inf+1]; // true :아님, false,맞음

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    unordered_map<int, vector<pair<int, int> > > sa_hashlist;
    string sa, sb; cin >> sa; cin >> sb;

    // 오일러의 체
    for (int i = 2; i <= inf; ++i) {
        
        if (!sz[i]) prime.push_back(i);
        for (int &e : prime) {
            if (i*e > inf) break; // 초과
            sz[i*e]= true;
            if (i%e==0) break; //합성수발견 -> 종료
        }
    }

    //sa에 대한 구간별 해싱
    for(int i = 0; i < (int)sa.size(); ++i) {   
        int h1 = 1, h2 = 1; // 이중해시,
        for (int j = i; j < (int)sa.size(); ++j) { //구간 i ~ j 까지의 해싱작업
            int val = sa[j]-'a';
            h1 = (h1 * prime[val])%mod;
            h2 = (h2 * prime[val + 26])%mod;

            sa_hashlist[h1].push_back({h2, j-i+1});
        }
    }

    int ans = 0;

    //sb에 대한 해싱 후 sa정보와 해싱
    for (int i = 0 ; i < (int)sb.size(); ++i) {
        int h1 = 1, h2 = 1; // 이중해시,
         for (int j = i ; j < (int)sb.size(); ++j) { //구간 i ~ j 까지의 해싱작업
            int val = sb[j]-'a';
            h1 = (h1 * prime[val])%mod;
            h2 = (h2 * prime[val + 26])%mod;

            for (auto &[h2_sa, len_sa] : sa_hashlist[h1]) {
                if (h2_sa == h2 && (j-i+1) == len_sa) ans = max(ans, len_sa);
            }
        }
    }
    cout << ans;
    return 0;

}