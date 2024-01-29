#include <iostream>
#include <vector>
#include <unordered_map>
#include <cctype>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    unordered_map<string,int> p_to_n;
    unordered_map<int,string> n_to_p;

    int N,M;
    cin >> N >> M;

    string name;
    int num=1;
    while (N--) {
        cin >> name;
        n_to_p[num] = name;
        p_to_n[name] = num;
        num++;
    }

    while (M--) {
        cin >> name;

        if (isdigit(name[0])) {
            cout << n_to_p[stoi(name)]<<'\n';
        }
        else {
            cout << p_to_n[name] <<'\n';
        }
    }
    return 0;
}