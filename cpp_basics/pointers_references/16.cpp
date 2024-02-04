#include <iostream>
 
using namespace std;
 
int main () {
   // declare simple variables
   int i;
 
   // declare reference variables
   int &r = i;
   
   i = 5;
   cout << "Value of i: " << i << endl;   // 5
   cout << "Value of i: " << r  << endl;  // 5

   i = 6;
   cout << "Value of i: " << i << endl;   // 6
   cout << "Value of i: " << r  << endl;  // 6
 
   r = 7;
   cout << "Value of i: " << i << endl;   // 7
   cout << "Value of r: " << r  << endl;  // 7

   return 0;
}