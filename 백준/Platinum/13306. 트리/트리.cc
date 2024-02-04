#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int mv = 2e5+1;
const int _2mv = mv * 2 + 1;
#define f(a,b,c) for(int a=b; a<c ; ++a)
int n , q;
int inp_parent[mv];
int p[mv];

int a[_2mv], b[_2mv], c[_2mv]; //query input arrays

//--union _ find 
int find(int a) { 
    return a == p[a] ? a : p[a] = find(p[a]);
}

bool _union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    p[min(a,b)] = max(a,b);
    return true;
}

// 문제 특성상 꼭 입력받자마자 출력할 필요 없음 -> 오프라인 쿼리
// 다 입력미리 받고 처리 후 출력도 가능
// 쿼리를 주어진 순서대로 처리하지 않고 나에게 유리한 순서대로 재배치해서 처리해 가는 것이 주 목적

// query에서 해당 단자가 끊어졌다는 것은 역순서로는 연결했다는 의미이기도 함
// 또한 반드시 N-1번 끊는 입력 받기에, 최종적으론 전부 끊겨있음 -> 따라서 역순으로 병합으로 생각해볼 수 있음

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //input
    cin >> n >> q;
    f(i,2,n+1) cin >> inp_parent[i];
    q+=(n-1);

    //query input
    f(i,0,q) {
        cin >> a[i];
        if (a[i]==0) cin >> b[i]; // cut query
        else cin >> b[i] >> c[i]; // request answer
    }
    //set parent init_value
    f(i,1,n+1) p[i]=i;

    //역순으로 쿼리처리
    vector<bool> ans;
    for(int i = q-1; i>=0;--i) {
        if (a[i] == 0) _union(b[i],inp_parent[b[i]]);
        else ans.push_back(find(b[i]) == find(c[i]));
    }
    reverse(ans.begin(), ans.end());
    for (bool val : ans) cout << (val ? "YES" : "NO") <<'\n';
    
}