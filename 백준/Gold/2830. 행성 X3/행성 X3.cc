#include <iostream>
using namespace std;

long long one[21];

int main(void) {
    int n; scanf("%d", &n);
    int max_idx = 0;
    int tmp;
    for (int i = 0; i <n; ++i) {
        scanf("%d", &tmp);
        int idx = 0;
        while (tmp)
        {
            if (tmp & 1) one[idx]++;
            tmp>>=1;
            ++idx;
        }
        // 최대 bit 자리수 구하기. 단 이 max_idx 자리는 포함x
        max_idx = max(max_idx, idx);
    }
    long long ans = 0;
    tmp = 1;
    for (int i = 0; i < max_idx; ++i) {
        ans += tmp * (one[i] * (n - one[i]));
        tmp <<= 1; 
    }
    printf("%lld", ans);
    return 0;
}

// 해당 index( 1 << idx 위치) 에서 친밀도가 적용 되는건
// 결국 해당 자리에서 0인 경우와 1인 경우의 수를 곱한 것이 경우의 수가 됨