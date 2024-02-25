#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define f(a,b,c) for(int a = b; a < c ; ++a)
#define START 0
#define CLEAR 32
int ans = 0;
//32의 의미. 도착햇음을 의미

int redgo[33] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11 ,12, 13, 14, 15, 16, 17, 18, 19, 20,
    32, 22, 23, 29, 25, 29, 27, 28, 29, 30,
    31, 20, CLEAR
}; // 32 의미 : 도착했음

int score[33] = { //스코어 점수
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
    20, 22, 24, 26, 28, 30, 32, 34, 36, 38,
    40, 13, 16, 19, 22, 24, 28, 27, 26, 25,
    30, 35, 0
};

int bluego[33]; //블루칸 도착시 이동해야하는 위치, 0 -> 의미없음

int dice[10]; //다이스 굴린 결과
int now_loc[4] = {0, }; //현재 말들의 위치

int next_go(int x, int move_cnt) { //시작지점, 이동해야 하는 길이
    if (bluego[x] != 0) { //첫 위치가 blue 화살표 존재시 그쪽으로 먼저이동
        --move_cnt;
        x = bluego[x];
    }
    while (move_cnt) {
        x = redgo[x];
        --move_cnt;
    }
    return x;
}

void back_track(int cnt, int total) { //back tracking 
    if (cnt == 10) {
        ans = max(ans, total);
        return;
    }

    for (int target = 0; target < 4; ++target) { //다이스 돌릴꺼 탐색
        int loc = now_loc[target]; //현재 타겟 말 위치
        if (loc == CLEAR) continue; //현재 타겟 말 위치가 이미 도착이면 스킵
        int nxt = next_go(loc,dice[cnt]); //다음 위치
        if (nxt == CLEAR) { //다음 위치 도달이 클리어 인 경우
            now_loc[target] = CLEAR;
            back_track(cnt + 1, total);
            now_loc[target] = loc;
        }
        else { //다음 위치가 도착이 아닌 경우
            bool cango = true;
            for (int other = 0; other < 4; ++other) { //다른 말 탐색해서 다른 말이 먼저 있는 경우 가면 안됨
                if (other == target) continue;
                if (now_loc[other] != CLEAR && now_loc[other] == nxt) {
                    cango = false;
                    break;
                }
            }
            if (cango) {
                now_loc[target] = nxt;
                back_track(cnt+1, total + score[nxt]);
                now_loc[target] = loc;
            }
        }
    }   
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    bluego[5] = 21;
    bluego[10] = 24;
    bluego[15] = 26;
    //input
    for(int i = 0; i < 10; ++i) cin >> dice[i];
    back_track(0, 0);
    cout << ans;
    return 0;
}