#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <algorithm>
#define f(a,b,c) for(int a=b;a<c;a++)
using namespace std;
int n, r, m , cnt_city;
unordered_map<string,int> city;
vector<int> go;
int gh[100][100];
const int inf = 1e9+1;

typedef struct _io {
    int node1, node2;
    int cost;
    int rcost;
} io;

vector<io> line;

void init(bool isnailro) {
    f(i,0,cnt_city) {
        f(j,0,cnt_city) {
            if(i==j) gh[i][j] = 0;
            else gh[i][j] = inf;
        }
    }
    for (int i = 0 ; i<(int)line.size();i++) {
        gh[line[i].node1][line[i].node2] = min(gh[line[i].node1][line[i].node2],(isnailro ? line[i].rcost : line[i].cost));
        gh[line[i].node2][line[i].node1] = gh[line[i].node1][line[i].node2];
        }
}

int cal(void) {
    f(i,0,cnt_city) {
        f(j,0,cnt_city) {
            f(k,0,cnt_city) {
                gh[j][k] = min(gh[j][k],gh[j][i] + gh[i][k]); 
            }
        }
    }
    int res = 0;
    for (int i = 1 ; i < (int)go.size();i++) {
        res += gh[go[i-1]][go[i]];
    }
    return res;
}
int main(void) {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> r;
    f(i,0,n) {
        string a ; cin >> a;
        if (city.find(a)==city.end()) city[a] = (int)city.size();
    }
    cnt_city = (int) city.size();
    cin >> m;
    go.resize(m);
    f(i,0,m) {
        string a; cin >> a; go[i] = city[a];
    }

    int p; cin >> p;
    line.resize(p);
    f(i,0,p) {
        string train_type, tmp;
        cin >> train_type;
        cin >> tmp; line[i].node1 = city[tmp];
        cin >> tmp; line[i].node2 = city[tmp];
        cin >> line[i].cost; line[i].cost*=2;
        if (train_type == "ITX-Saemaeul" || train_type == "ITX-Cheongchun" || train_type == "Mugunghwa") line[i].rcost = 0;
        else if (train_type =="S-Train" || train_type =="V-Train") line[i].rcost = line[i].cost/2;
        else line[i].rcost = line[i].cost;
    }

    init(false); int not_railro = cal()/2;
    init(true); int railro = cal()/2 + r;
    if (railro < not_railro) cout <<"Yes";
    else cout <<"No";
    return 0;
}