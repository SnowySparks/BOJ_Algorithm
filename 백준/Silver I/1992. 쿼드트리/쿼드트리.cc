#include <iostream>
#include <string>
#include <algorithm>
#define max_l 1000000
using namespace std;

string table[64];

//start locationg row, column , length
void check(int rs, int cs, int l) {
    if (l== 1) {cout << table[rs][cs];
        return ;
    }
    char first_valuse = table[rs][cs];
    bool need_break = false;
    for (int i = rs ; i <rs+l; i++) {
        for (int j = cs ; j <cs+l; j++) {
            if (first_valuse != table[i][j]) {
                need_break = true;
                break;
            }
        }
        if (need_break) break;
    }
    if (!need_break) {cout << first_valuse;}
    else {
        cout << '(';
        check(rs, cs, l/2);
        check(rs,cs+l/2,l/2);
        check(rs+l/2,cs,l/2);
        check(rs+l/2,cs+l/2,l/2);
        cout << ')';
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n ; cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> table[i];
    }

    check(0,0,n);

    return 0;

}