#include<iostream>
#include<stack>
using namespace std;

int priority(char oper) {
    if (oper == '+' || oper == '-') return 0;
    if (oper == '*' || oper == '/') return 1;
    else return -1;
}

int operating(int a, int b, char oper) {
    switch (oper)
    {
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '*':
        return a*b;
        break;
    case '/':
        return a/b;
        break;
    }
    return 0;
}

string postfix(const string &midfix) {
    string s = "";
    stack<char> oper;
    for (char ch : midfix) {
        if (ch >= '0' and ch <= '9') s.push_back(ch);
        else if (ch == '(') oper.push(ch);
        else if (ch == ')') {
            while (!oper.empty() && oper.top() != '(') {
                s.push_back(oper.top());
                oper.pop();
            }
            oper.pop();
        }
        else {
            while (!oper.empty() && priority(oper.top()) >= priority(ch)) {
                s.push_back(oper.top());
                oper.pop();                
            }
            oper.push(ch);
        }
    }
    while (!oper.empty()) {
        s.push_back(oper.top()); oper.pop();
    }
    return s;
}

int calc (const string &pfix) {
    stack<int> num;
    int ans = 0;
    for (char ch : pfix) {
        if (ch >= '0' && ch <='9') num.push(ch-'0');
        else {
            int n2 = num.top();
            num.pop();
            int n1 = num.top();
            num.pop();
            num.push(operating(n1,n2,ch));
        }
    }
    return num.top();
}



int main(int argc, char** argv)
{
	int T = 10;
	// freopen("input.txt", "r", stdin);

	for(int test_case = 1; test_case <= T; ++test_case)
	{
        int n; string p;
        cin >> n; cin >> p;
        cout << '#' << test_case <<' ' << calc(postfix(p)) << '\n';
	}
	return 0;
}