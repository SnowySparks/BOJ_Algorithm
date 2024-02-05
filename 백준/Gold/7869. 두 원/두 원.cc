#include <iostream>
#include <cmath>
using namespace std;
double aabs(double a) {
    return a>=0?a:-a; }

double min(double a, double b) {
    return a>=b?b:a; }

double cos_raw(double debtor, double a, double b){// a,b사이 각의 코사인값 구하기, 해당 각 기준 대변, 사이변1,사이변2 
    return ((a*a + b*b - debtor*debtor)/(2*a*b));
}

int main(void) {
    ios_base::sync_with_stdio(false);cin.tie(0); cout<<fixed; cout.precision(3);
    double x1, y1, r1, x2, y2 ,r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)); //circle center distance
    if (d >= (r1+r2)) {cout << "0.000"; return 0;} 
    if (aabs(r1-r2)>=d) {cout << M_PI*min(r1,r2)*min(r1,r2); return 0;}
    double theta1 = acos(cos_raw(r2,r1,d)), theta2 = acos(cos_raw(r1,r2,d)); 
    cout << r1*r1*theta1 + r2*r2*theta2 - sin(theta1)*r1*d;
    return 0;
    

}