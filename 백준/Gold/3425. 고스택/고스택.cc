#include <iostream>
#include <deque>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
using ll = long long;
vector<string> cmd;
deque<ll> numlst;

deque<ll> st;

string inp;
int n, first;
ll tmp;
bool error = false;
int numlst_loc = 0;
const ll max_threshold = 1e9;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    while (1)
    {
        cin >> inp;
        if (inp == "QUIT") break;
        else if (inp == "END") {
            cin >> n;
            while (n--)
            {
                cin >> first;
                st.clear();
                error = false;
                st.push_back(first);
                numlst_loc = 0;

                for (const string &c : cmd) {
                    if (c == "NUM") {
                        st.push_back(numlst[numlst_loc]);
                        numlst_loc++;
                    }
                    else if (c == "POP") {
                        if (st.empty()) {
                            error = true;
                            break;
                        }
                        else st.pop_back();
                    }
                    else if (c == "INV") {
                        if (st.empty()) {
                            error = true;
                            break;
                        }
                        else {
                            ll x = st.back(); st.pop_back();
                            st.push_back(-x);
                        }
                    }
                    else if (c == "DUP") {
                        if (st.empty()) {
                            error = true;
                            break;
                        }
                        st.push_back(st.back());                        
                    }
                    else if (c == "SWP") {
                        if ((int)st.size() < 2) {
                            error = true;
                            break;
                        }
                        ll first = st.back(); st.pop_back();
                        ll second = st.back(); st.pop_back();
                        st.push_back(first);
                        st.push_back(second);
                    }
                    else if (c == "ADD") {
                        if ((int)st.size() < 2) {
                            error = true;
                            break;
                        }
                        ll first = st.back(); st.pop_back();
                        ll second = st.back(); st.pop_back();

                        if (abs(first + second) > max_threshold) {
                            error = true;
                            break;
                        }
                        st.push_back(first+ second);                        
                    }
                    else if (c == "SUB") {
                        if ((int)st.size() < 2) {
                            error = true;
                            break;
                        }
                        ll first = st.back(); st.pop_back();
                        ll second = st.back(); st.pop_back();
                        if (abs(second - first) > max_threshold) {
                            error = true;
                            break;
                        }

                        st.push_back(second - first);                        
                    }
                    else if (c == "MUL") {
                        if ((int)st.size() < 2) {
                            error = true;
                            break;
                        }
                        ll first = st.back(); st.pop_back();
                        ll second = st.back(); st.pop_back();
                        if (abs(first * second) > max_threshold) {
                            error = true;
                            break;
                        }
                        st.push_back(first * second);                        
                    }
                    else if (c == "DIV") {
                        if ((int)st.size() < 2) {
                            error = true;
                            break;
                        }
                        // 피제수 / 제수 = ?
                        ll first = st.back(); st.pop_back(); //제수
                        ll second = st.back(); st.pop_back(); //피제수 

                        if (first == 0) {
                            error = true;
                            break;
                        }

                        if (second > 0) {
                            if (first > 0) st.push_back(second / first);
                            else st.push_back( - (second / abs(first)));
                        }
                        else {
                            if (first > 0) st.push_back( - (abs(second) / first));
                            else st.push_back( abs(second) / abs(first));
                        }
                    }
                    else if (c == "MOD") {
                        if ((int)st.size() < 2) {
                            error = true;
                            break;
                        }
                        // 피제수 / 제수 = ?
                        ll first = st.back(); st.pop_back(); //제수
                        ll second = st.back(); st.pop_back(); //피제수 

                        if (first == 0) {
                            error = true;
                            break;
                        }

                        if (second > 0) {
                            if (first > 0) st.push_back(second % first);
                            else st.push_back(  (second % abs(first)));
                        }
                        else {
                            if (first > 0) st.push_back( - (abs(second) % first));
                            else st.push_back( - abs(second) % abs(first));
                        }
                    }
                }
                if (error || (int)st.size() != 1) {
                    cout << "ERROR\n";
                }
                else cout << st.front() << '\n';
            }
            cout << '\n';
            cmd.clear();
            numlst.clear();
            numlst_loc=0;
            st.clear();

        }
        else if (inp == "NUM") {
            cin >> tmp;
            numlst.push_back(tmp);
            cmd.push_back(inp);
        }
        else {
            cmd.push_back(inp);
        }
    }
    

    return 0;
}