#include <iostream>
#include <vector>
using namespace std;
using ul = unsigned long long;

ul pow(ul n, ul p, ul mod) { // fast n^p % mod
    ul res = 1, mul = n;
    while(p) {
        if (p&1) res = (res * mul)%mod;
        mul = (mul * mul)%mod;
        p>>=1;
    }
    return res;
}

// 밀러 - 라빈 소수 판정법
// N 이 2가 아닌 소수인 경우에 대해 판정
// a^(N-1) == 1 (mod N) 이라는 것 (N - 1 == d *2^s)에서 기인 ( d : 홀수 )
// 이때 a^(d * 2^(r) ), 0<=r<s mod N 을 연산함
// a^d mod N = 1 이거나, a^(d * 2^r) mod N == -1 인 경우 N은 소수라고 판정 (이때 r범위 값중 아무거나 하나만 만족해도 인정)
// 이때 a는 N보다 작은 어느 양의 정수
bool miler(ul n, ul a) { // n : 소수판정하고싶은 값, a : 어느 임의의 소수
    if (a % n == 0) return true; // 해당 알고리즘에서 a 입력이 소수이니 a%n==0 이라는건 n == a인 경우와 같은 것
    ul k = n-1;
    while ( true ){
        ul temp = pow(a, k, n); //a^(n-1) % n
       if(temp == n-1) return true; // 나머자가 -1이 나왔다는 것 -> 이후 계속 -1 나온다는 뜻 -> 즉 소수라고 판정
       if (k%2) return ((temp == 1) || temp == -1); // 
       k>>=1;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int base[] = {2, 7, 61};
    int n; cin >> n;
    int ans = 0;
    //2xy + x + y = s
    //4xy + 2x + 2y + 1 = 2s + 1
    //(2x + 1)(2y + 1) = 2s + 1 => 2s +1 은 무조건 합성수
    for (int k=0;k<n;++k) {
        ul a; cin >> a;
        a =2*a+1; 

        for (int i = 0 ; i < 3; ++i) {
            if (miler(a,base[i])==false) {
                ++ans; break;
            }
        }
    }
    cout << (n - ans) ;
    return 0;
}