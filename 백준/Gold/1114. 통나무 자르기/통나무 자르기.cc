#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int inf = 1e9 + 7;
int inp[10002];
vector<int> loc; //입력값중 중복을 제거한 위치들 + ( 마지막 L 추가)
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int L, C, K;
    cin >> L >> K >> C;
    // l : 통나무 길이, c : 통나무 자를 수 있는 최대 횟수, k = 위치갯수
    for (int i = 0; i < K; ++i)
        cin >> inp[i];
    sort(inp, inp + K);
    loc.push_back(inp[0]);

    for (int i = 1; i < K; ++i)
    {
        if (loc.back() != inp[i])
            loc.push_back(inp[i]);
    }

    loc.push_back(L);

    int loc_size = loc.size();
    int right = L;
    int first_loc = L;
    int cnt = C;

    int ans_length = L, ans_first_loc = L;
    int l = 1, r = L;

    // for (int &v : loc) {
    //     cout << v <<' ';
    // }
    // cout << '\n';
    while (l <= r) //이분탐색
    {
        cnt = C;
        right = L;
        int mid = (l + r) >> 1; //최대 통나무 길이

        // 오른쪽부터 탐색해서 최대 허용 크기 mid 넘어서는 것에 대한 처리
        // 오른쪽부터 최대한 크게 잘라야 왼쪽 부분이 가장 작게 남음 (그리디)
        for (int i = loc_size - 1; i >= 0; --i)
        {
            if ( right - loc[i] > mid ) {
                if (loc[i+1] - loc[i] > mid) { //직전 위치와 거리가 mid넘으면 불가능한 경우
                    // cout <<"here" <<  mid <<' ' <<i << '\n';
                    cnt = -1;
                    break;
                }
                cnt--;
                right = loc[i+1];
            }
        }

        if (cnt > 0) right = loc[0]; //자르는 횟수 남은 경우, 가장 왼쪽부분 컷 가능 -> 그리디


// 연산 결과, right는 가능한 가장 왼쪽으로 감
// 불가능 조건
        if ( cnt < 0 || right > mid) {
            // cout << "impossoble : " << cnt <<' ' <<mid << '\n';
            l = mid + 1;
        }
// 가능 조건
        else {
            r = mid - 1;
            ans_length = mid;
            ans_first_loc = right;
        }
    }
    cout << ans_length  << ' ' <<ans_first_loc;
    return 0;
}