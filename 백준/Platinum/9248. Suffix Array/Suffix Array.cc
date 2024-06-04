#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 5e5+10;
int sa[inf], group[inf], temp[inf], lcp[inf]; // suffix array, group이용한 sort, 임시 그룹 번호
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int n = s.size(); // n : 문자열 길이

    // first setting 
    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        group[i] = s[i];
    }

    for (int d = 1; d < n; d <<= 1) { //문자 탐색 위치 
    // 접미사 비교함수 
        auto comp = [&d, &n](int a, int b) -> bool {
            // 자신의 위치의 문자를 비교( 어느 그룹에 있는가?), a가 더 앞서는지에 대한 함수
            if (group[a] != group[b]) return group[a] < group[b];
            // 동일 그룹에 있는 경우 -> d칸 뒤 문자열의 비교
            a += d; b += d;
            return (a < n && b < n) ? group[a] < group[b] : a > b; 
        };

        // 접미사 비교함수로 정렬
        sort(sa, sa+n, comp);
        memset(temp, 0, sizeof(temp)); //reset, 

        for(int i = 1; i < n; ++i) {
            if (comp(sa[i-1], sa[i])) temp[i] = temp[i-1]+1;
            else temp[i] = temp[i-1];
        }

        // 새 그룹 번호로 
        for (int i = 0; i < n; ++i) group[sa[i]] = temp[i];
        if (temp[n-1] == n-1) break; // 그룹이 n-1개 == 모든 접미사에 대한 정렬 완료
    }

    // suffix array 확인
    // for (int i = 0; i < n; ++i) {
    //     cout << sa[i] + 1 << '\n';
    // }

// lcp 
    for (int i = 0, k = 0; i < n; ++i, k = max(k-1, 0)) {
        // group[i] = s[i:]가 sa의 몇 번째에 있는가 (group[sa[i]] = i)
        if (group[i] == n-1) continue; //마지막 접미사->  암것도 안함
        for (int j = sa[group[i]+1]; s[i+k] == s[j+k]; ++k);
        lcp[group[i]] = k;
    }

    for (int i = 0; i < n; ++i) cout << sa[i]+1 <<' ';
    cout << '\n';
    cout <<"x";
    for (int i = 0; i < n-1; ++i) cout << ' ' << lcp[i];

    return 0;
}