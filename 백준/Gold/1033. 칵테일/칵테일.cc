#include <iostream>
#include <vector>
#include <cstring>
#define f(a, b, c) for (int a=b; a<c;++a)
using namespace std;
using ll = long long;
int n;
int ans[10];
bool v[10];
struct info {
    int to, p, q;
};

vector<int> gh[11];
int gcd(int a, int b) {
    int tmp;
    while (b) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

// a, b에 변한 량
void dfs(int node, int mult) {
    ans[node] *= mult;
    v[node] = true;
    for (int &child : gh[node]) {
        if (!v[child]) dfs(child, mult);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i,0,n) ans[i] = 1;
    f(i, 0, n-1) {
        int a, b, p, q; cin >> a >> b >> p >> q;
        int g = gcd(p, q);
        //기약분수화
        p /= g;
        q /= g;

        //변화량 적용 - 
        // a / b == p / q 이니까 b * p == a * q 이라는 것과 같음 a , b 둘다
        // ex a = 7x b = 4y 였는데 p/q = 3/2 이면 12y = 14x -> 6y = 7x이며 y =7, x = 6 이 됨
        // 즉 이 경우 a1 최소 변화배수는 6, b1 최소 변화배수는 7이됨
        // a, b 각각 연결된 노드들에도 전부 업데이트 함
        int a1 = ans[b] * p;
        int a2 = ans[a] * q;

        int lgcd = gcd(a1, a2); //a, b의 최대공약수
        memset(v, 0, sizeof(v));

        //dfs 접근
        dfs(a, a1/lgcd); //a 포함 a와 관련된 (연결된) 노드들을 전부 업데이트. a변화량만큼
        dfs(b, a2/lgcd);//b 포함 b와 관련된 (연결된) 노드들을 전부 업데이트. b변화량만큼

        //연결
        gh[a].push_back(b);
        gh[b].push_back(a);
    }
    f(i, 0, n) cout << ans[i] << ' ';
    return 0;
}