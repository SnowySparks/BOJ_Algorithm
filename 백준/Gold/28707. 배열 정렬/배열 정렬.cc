#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;
using ll = long long;
struct cmd {
    int l, r, cost;
    cmd(int l = 0, int r = 0, int cost = 0) : l(l),r(r),cost(cost) {}
};

int p1[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000};
// string 대신 각 자리 수를 이용하는 방법 있음 ,, 첫째자리가 가장 앞 ,, 마지막 자리가 가장 뒤 // --> int형으로도 가능

int n, m;
int start_num = 0, temp;
string ed;
int num_ed;
vector<cmd> clst;
ll ans = 1e18;

using ar = pair<ll,int>; //for priority queue

int num_out(int num, int loc) {
    return (num % p1[loc+1])/p1[loc];
}

void chg(int &num, int l, int r) {
    int lnum = num_out(num,l);
    int rnum = num_out(num,r);

    num = num - (lnum * p1[l]) + rnum * p1[l] - (rnum * p1[r]) + lnum * p1[r];
}

void change(ar &target,const cmd &cd) {
    chg(target.second,cd.l,cd.r);
    target.first+=cd.cost;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0 ; i < n; i++) {
        cin >> temp; temp--;
        ed.push_back('0' + temp);
        start_num+= temp*p1[i];
    }
    sort(ed.begin(),ed.end(),greater<>());
    num_ed = stoi(ed);

    cin >> m;
    clst.resize(m);
    for (int i = 0 ; i < m ; i++) {
        cin >> clst[i].l >> clst[i].r >> clst[i].cost;
        clst[i].l--; clst[i].r--;
    }

    unordered_map <int,ll> vis;
    vis[start_num] = 0;
    priority_queue<ar, vector<ar>, greater<> > pq;
    pq.push({0,start_num});

    while(!pq.empty()) {
        ar loc = pq.top(); pq.pop();
        if (loc.second == num_ed) {
            ans = min(ans,loc.first);
            break;
        }
        for (int i = 0 ; i < m ; i ++) {
            ar nloc = loc;
            change(nloc,clst[i]);
            if (vis.find(nloc.second)== vis.end() || vis[nloc.second] > nloc.first) {
                vis[nloc.second] = nloc.first;
                pq.push(nloc);
            }
        }
    }

    cout << (ans >= 1e18 ? -1 : ans);
    return 0;
}