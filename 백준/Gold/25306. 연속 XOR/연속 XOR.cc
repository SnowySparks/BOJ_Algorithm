#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 00 ^ 01 ^ 10 ^ 11 = 00 임을 이용함 -> 100 101 110 111 / 1000 1001 1010 1011 ...
// 00^00 = 00
// 4*b ~ 4*b+3 구간
int main(void) {
    long long a,b; cin >> a >>b;
    long long answer=a;
    long long end_a, start_b; //a ~ end_a , start_b ~ b 
    //값 차이가 7 이하면 그냥 연산
    if (b-a <=7) {
        for (long long i = a+1; i <=b ; i++) {
            answer ^= i;
        }
        cout << answer;
        return 0;
    }

    start_b = b/4*4;
    end_a = (a/4 +1)*4 -1;
    for (long long i = a+1; i<= end_a; i++) {
        answer ^=i;
    }
    for (long long i = start_b ; i <= b; i++) {
        answer ^=i;
    }
    cout << answer;
    return 0;
}