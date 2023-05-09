#include <iostream> 

using namespace std;

int main(){
    // can do either method, but doing it next the the variable name looks nicer 
    // while these are unintilized, they will contain garbage data (like all variables)
    int *foo_int_ptr;
    double* double_ptr; 
    int *int_ptr {nullptr};

    int num{10};
    cout << "the value of num is " << num << endl;
    cout << "sizeof of num is: " << sizeof num << endl;
    cout << "address of num is " << &num << endl; 
}