#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int ans = 0;
const int max_move = 10;
int move_left(vector<vector<int> > &lst) {
    int res = 0;
    deque<int> dq;
    bool dq_bool = false;
    for (int r = 0; r < n; ++r) {
        dq_bool = false;
        for (int c = 0; c < n; ++c) {
            if (lst[r][c] != 0) {
                if (dq.empty() || dq.back() != lst[r][c] || dq_bool) {
                    dq.push_back(lst[r][c]);
                    dq_bool = false;

                }
                else if (!dq_bool) {
                    *dq.rbegin() *= 2;
                    dq_bool = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = 0;
        while(!dq.empty()) {
            lst[r][idx] = dq.front();
            res = max(res, dq.front());
            dq.pop_front();
            ++idx;
        }
    }
    return res;
}

int move_right(vector<vector<int> > &lst) {
    int res = 0;
    deque<int> dq;
    bool dq_bool = false;
    for (int r = 0; r < n; ++r) {
        dq_bool = false;
        for (int c = n-1; c >= 0; --c) {
            if (lst[r][c] != 0) {
                if (dq.empty() || dq.front() != lst[r][c] || dq_bool) {
                    dq.push_front(lst[r][c]);
                    dq_bool = false;
                }
                else if (dq_bool == false) {
                    *dq.begin() *= 2;
                    dq_bool = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = n-1;
        while(!dq.empty()) {
            lst[r][idx] = dq.back();
            res = max(res, dq.back());
            dq.pop_back();
            --idx;
        }
    }
    return res;
}

int move_up(vector<vector<int> > &lst) {
    int res = 0;
    deque<int> dq;
    bool dq_bool = false;
    for (int c = 0; c < n; ++c) {
        dq_bool = false;
        for (int r = 0; r < n; ++r) {
            if (lst[r][c]) {
                if (dq.empty() || dq.back() != lst[r][c] || dq_bool) {
                    dq.push_back(lst[r][c]);
                    dq_bool = false;
                }
                else if (dq_bool == false) {
                    *dq.rbegin() *= 2;
                    dq_bool = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = 0;
        while (!dq.empty()) {
            lst[idx][c] = dq.front();
            res = max(res, dq.front());
            ++idx;
            dq.pop_front();
        }
    }
    return res;
}

int move_down(vector<vector<int> > &lst) {
    int res = 0;
    deque<int> dq;
    bool dq_bool = false;
    for (int c = 0; c < n; ++c) {
        dq_bool =false;
        for (int r = n-1; r >= 0; --r) {
            if (lst[r][c]) {
                if (dq.empty() || dq.front() != lst[r][c] || dq_bool) {
                    dq.push_front(lst[r][c]);
                    dq_bool = false;
                }
                else if (dq_bool == false) {
                    *dq.begin() *= 2;
                    dq_bool = true;
                }
            }
            lst[r][c] = 0;
        }
        int idx = n-1;
        while (!dq.empty()) {
            lst[idx][c] = dq.back();
            res = max(res, dq.back());
            --idx;
            dq.pop_back();
        }
    }
    return res;
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
    if (cnt == max_move) {
        return;
    }
    vector<vector<int> > backup(a);
    int res = 0;
    res = move_left(a);
    if (!issame(a, backup) && res * (1 << (max_move - (cnt+1))) > ans ) {
        ans = max(ans, res);
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    res = move_right(a);
    if (!issame(a, backup) && res * (1 << (max_move - (cnt+1))) > ans )  {
        ans = max(ans, res);
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    res =move_up(a);
    if (!issame(a, backup) && res * (1 << (max_move - (cnt+1))) > ans )  {
        ans = max(ans, res);
        dfs(cnt+1, a);
    }
    copy(backup.begin(), backup.end(), a.begin());
    res = move_down(a);
    if (!issame(a, backup) && res * (1 << (max_move - (cnt+1))) > ans )  {
        ans = max(ans, res);
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