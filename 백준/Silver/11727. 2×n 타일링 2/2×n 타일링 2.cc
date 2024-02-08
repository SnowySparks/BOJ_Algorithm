#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1000000000

int table[1001];

int main(void) {
    int b;
    cin >> b;

    table[0]=0;
    table[1]=1;
    table[2]=3;

    for (int i=3; i<=b; i++) {
        table[i]=(table[i-1]+table[i-2]*2)%10007;
    }
    cout<<table[b]<<endl;

    return 0;

}