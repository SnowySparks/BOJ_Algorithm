#include <iostream>
using namespace std;
int n,l=1,r=1,total ,ans = 1;
int main(){
    cin >> n;
    while(r <= n) {
        if(total < n) total += r++;
        else{
            if(total == n) ans++;
            total -= l++;
        }
    }
    cout << ans;
}