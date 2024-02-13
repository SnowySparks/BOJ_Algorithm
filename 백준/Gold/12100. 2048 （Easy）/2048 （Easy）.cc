#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int ans = 0;
const int max_move = 5;
void move_left(vector<vector<int> > &lst) {
    deque<int> dq;
    deque<bool> dq_bool;
    for (int r = 0; r < n; ++r) {
        dq_bool.clear();
        for (int c = 0; c < n; ++c) {
            if (lst[r][c] != 0) {
                if (dq.empty() || dq.back() != lst[r][c] || dq_bool.back()) {
                    dq.push_back(lst[r][c]);
                    dq_bool.push_back(false);
                }
                else if (dq_bool.back() == false) {
                    *dq.rbegin() *= 2;
                    *dq_bool.rbegin() = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = 0;
        while(!dq.empty()) {
            lst[r][idx] = dq.front();
            dq.pop_front();
            ++idx;
        }
    }
}

void move_right(vector<vector<int> > &lst) {
    deque<int> dq;
    deque<bool> dq_bool;
    for (int r = 0; r < n; ++r) {
        dq_bool.clear();
        for (int c = n-1; c >= 0; --c) {
            if (lst[r][c] != 0) {
                if (dq.empty() || dq.front() != lst[r][c] || dq_bool.front()) {
                    dq.push_front(lst[r][c]);
                    dq_bool.push_front(false);
                }
                else if (dq_bool.front() == false) {
                    *dq.begin() *= 2;
                    *dq_bool.begin() = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = n-1;
        while(!dq.empty()) {
            lst[r][idx] = dq.back();
            dq.pop_back();
            --idx;
        }
    }
}

void move_up(vector<vector<int> > &lst) {
    deque<int> dq;
    deque<bool> dq_bool;
    for (int c = 0; c < n; ++c) {
        dq_bool.clear();
        for (int r = 0; r < n; ++r) {
            if (lst[r][c]) {
                if (dq.empty() || dq.back() != lst[r][c] || dq_bool.back()) {
                    dq.push_back(lst[r][c]);
                    dq_bool.push_back(false);
                }
                else if (dq_bool.back() == false) {
                    *dq.rbegin() *= 2;
                    *dq_bool.rbegin() = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = 0;
        while (!dq.empty()) {
            lst[idx][c] = dq.front();
            ++idx;
            dq.pop_front();
        }
    }
}

void move_down(vector<vector<int> > &lst) {
    deque<int> dq;
    deque<bool> dq_bool;
    for (int c = 0; c < n; ++c) {
        dq_bool.clear();
        for (int r = n-1; r >= 0; --r) {
            if (lst[r][c]) {
                if (dq.empty() || dq.front() != lst[r][c] || dq_bool.front()) {
                    dq.push_front(lst[r][c]);
                    dq_bool.push_front(false);
                }
                else if (dq_bool.front() == false) {
                    *dq.begin() *= 2;
                    *dq_bool.begin() = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = n-1;
        while (!dq.empty()) {
            lst[idx][c] = dq.back();
            --idx;
            dq.pop_back();
        }
    }
}

void vprint(const vector<vector<int> > &a) {
    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < n; ++c) {
            cout << a[i][c] <<' ';
        }
        cout <<'\n';
    }
}

bool issame(const vector<vector<int> > &a, const vector<vector<int> > &b) {
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (a[r][c] != b[r][c]) return false;
        }
    }
    return true;
}

int max_val(const vector<vector<int> > &a) {
    int res = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            res = max(res, a[r][c]);
        }
    }
    return res;
}


void dfs(int cnt, vector<vector<int> > a) {
    ans = max(max_val(a),ans);
    if (cnt == max_move) {
        ans = max(ans, max_val(a));
        return;
    }
    int now_max = max_val(a);
    if (now_max * (1 << (max_move - cnt) ) <= ans ) return;
    vector<vector<int> > backup(a);

    move_left(a);
    if (!issame(a, backup)) {
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    move_right(a);
    if (!issame(a, backup)) {
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    move_up(a);
    if (!issame(a, backup)) {
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    move_down(a);
    if (!issame(a, backup)) {
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    vector<vector<int> > arr(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> arr[i][j];
        }
    }
    ans = max_val(arr);
    dfs(0, arr);
    cout << ans;
    return 0;
}