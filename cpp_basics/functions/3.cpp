#include<iostream>
  
using namespace std;
  
void fun(int &x) { 
    x = 20; 
} 
    
int main() { 
    int x = 10; 
    fun(x); 
    cout << "New value of x is " << x; // 20
    return 0; 
}