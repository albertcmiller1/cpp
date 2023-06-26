#include <iostream>
 
using namespace std;
 
int main () {
   // declare simple variables
   int i;
 
   // declare reference variables
   int &r = i;
   
   i = 5;
   cout << "Value of i: " << i << endl;
   cout << "Value of i: " << r  << endl;

   i = 6;
   cout << "Value of i: " << i << endl;
   cout << "Value of i: " << r  << endl;
 
   r = 7;
   cout << "Value of i: " << i << endl;
   cout << "Value of r: " << r  << endl;

   return 0;
}