#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
pair<double, double> arr[10];
const double tolerance = 1e-12;
int n;

double cal(int loc) { // arr 왼쪽 점 기준
    double l = arr[loc].first, r=arr[loc+1].first;
    // cout << l <<' ' << r << '\n';
    double lF = 0.0, rF = 0.0;
    double res = l;
    while (l + tolerance < r)
    {
        double mid = (l + r) / 2;

        lF = 0.0; rF = 0.0;

        f(i, 0, loc+1) lF += arr[i].second / ((mid - arr[i].first)*(mid - arr[i].first));
        f(i, loc+1, n) rF += arr[i].second / ((arr[i].first - mid)*(arr[i].first - mid));

        // cout << mid <<' ' << lF <<' ' << rF << '\n';

        res = mid;
        if (lF > rF) l = mid;
        else r = mid;
    }
    return res;
    
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cout<<fixed;
    cout.precision(10);
    vector<double> ans;
    int T; cin >> T;
    f(tc, 1, T+1) {
        ans.clear();
        cin >> n;
        f(i, 0, n) cin >> arr[i].first;
        f(i, 0, n) cin >> arr[i].second;
        sort(arr, arr+n);
        f(i, 0, n-1) {
            ans.push_back(cal(i));
        }
        cout << '#' << tc;
        f(i, 0, n-1) cout <<' ' << ans[i];
        cout << '\n';
    }
}