#include <iostream>
using namespace std;

int main(void) {
    int x, y, w, s;
    scanf("%d %d %d %d",&x, &y, &w, &s);
    x = abs(x); y=abs(y);
    if (2*w <= s) {
        printf("%lld", (1LL*(x+y)*w));
    }
    else {
        long long max_v = max(x, y), min_v= min(x, y);
        long long left = max_v - min_v;
        long long mv = min_v * s;

        if (w <= s) mv += (left * w);
        else mv += (left/2*2*s) + (left&1)*w;
        printf("%lld", mv);
    }
    return 0;
}