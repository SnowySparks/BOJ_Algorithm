#include <iostream>
#include <cstring>
#include <algorithm>
using ll = long long;
#define f(a,b,c) for(int a=b; a<c; a++)
using namespace std;

int n = 10; //지도범위 r, c
int m; //이동시간
int A; //배터리 갯수
int dr[5] = {0, -1, 0, 1, 0};
int dc[5] = {0, 0, 1, 0, -1}; //stay up, right, down, left

int Amove[101], Bmove[101];

struct BatteryInfo {
    int r, c, range, power;
    void clear() {
        r =0; c=0; range=0; power=0;
    }
};
BatteryInfo binfo[8]; //배터리 정보 저장 공간

int aBattery[8], bBattery[8];

bool indist(int r, int c, const BatteryInfo &battery) {
    return abs(r - battery.r) + abs(c - battery.c) <= battery.range;
}

int powerBattery(int x) {
    if (x == -1) return 0;
    return binfo[x].power;
}

bool comp(int a1, int a2) {
    return powerBattery(a1) > powerBattery(a2);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int ans = 0;
    for (int tc = 1 ;tc <= T; ++tc) {
        //input
        ans = 0;
        cin >> m >> A;
        f(i, 1, m+1) cin >> Amove[i];
        f(i, 1, m+1) cin >> Bmove[i];
        f(i, 0, A) {
            binfo[i].clear();
            cin >>binfo[i].c >> binfo[i].r >> binfo[i].range >> binfo[i].power;
        }
        int ar =1, ac = 1, br= 10, bc = 10; //a, b 각각정보

        f(i, 0, m+1) {//이동
            ar += dr[Amove[i]]; ac+=dc[Amove[i]];
            br += dr[Bmove[i]]; bc+=dc[Bmove[i]];
            memset(aBattery, -1, sizeof(aBattery));
            memset(bBattery, -1, sizeof(bBattery));
            //각각 배터리 거리 측정수 범위 안?
            f(k, 0, A) {
                //a먼저
                if (indist(ar, ac, binfo[k])) {
                    aBattery[k] = k;
                }
                //b
                if (indist(br, bc, binfo[k])) {
                    bBattery[k] = k;
                }               
            }
            sort(aBattery, aBattery+A,comp);
            sort(bBattery, bBattery+A,comp);
            // cout << "Time :" << i  <<'\n';
            // cout <<"A:";
            // f(d, 0, A) cout << aBattery[d] <<"::"<<powerBattery(aBattery[d]) <<' ';
            // cout <<"\nB:";
            // f(d, 0, A) cout << bBattery[d] <<"::"<<powerBattery(bBattery[d]) <<' ';
            // cout<<'\n';
            if (aBattery[0] != bBattery[0]) {
                ans += powerBattery(aBattery[0]) + powerBattery(bBattery[0]);
            }
            else {
                ans += max(powerBattery(aBattery[1]) + powerBattery(bBattery[0]), powerBattery(aBattery[0]) + powerBattery(bBattery[1]));
            }
        }
        cout << '#' <<tc <<' ' << ans << '\n';
    }

    return 0;
}