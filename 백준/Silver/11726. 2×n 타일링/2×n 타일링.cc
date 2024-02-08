#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(void) {
   int a;
   cin>>a;

   vector<int> table(a+1);
   table[1]=1;
   table[2]=2;

   for (int i=3;i<=a;i++) {
      table[i]=(table[i-1]+table[i-2])%10007;
   }
   cout<<table[a]<<endl;
   return 0;
}

