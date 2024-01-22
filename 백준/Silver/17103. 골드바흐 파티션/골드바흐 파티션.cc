#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
using namespace std;
vector<int> primes;
const int inf = 1e6+1;
int arr[inf];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    for (int i = 2; i <=inf ; ++i) {
        if (arr[i] == 0) primes.push_back(i);
        for (int j : primes) {
            if ((long long) i * j >= (long long) inf) break;
            arr[i*j] = j;
            if (i%j==0) break;
        }
    }
    unordered_map<int, bool> mp;
    for (int j : primes) mp[j]=true;

    int t; cin >> t;
    while (t--) {
        int cnt = 0;
        int tmp; cin >> tmp;
        for (int j : primes) {
            if (j > tmp/2) break;
            if (mp.find(tmp - j)!=mp.end()) cnt++;
        }
        cout << cnt <<'\n';
    }


}
