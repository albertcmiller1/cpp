#include <iostream> 

using namespace std;

int main(){

    int *p;

    cout << "the value of p is " << p << endl;
    cout << "address of p is " << &p << endl; 
    cout << "sizeof of p is: " << sizeof p << endl;
    cout << endl;

    p = nullptr;

    cout << "the value of p is " << p << endl; // nullptr address
    cout << "address of p is " << &p << endl; 
    cout << "sizeof of p is: " << sizeof p << endl;
    cout << endl;
}