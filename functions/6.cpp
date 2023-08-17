#include <iostream>
  
using namespace std;
  
int global_var = 42;
  
// function to return reference value
int& ReturnReference()
{
    return global_var;
}
  
int main()
{
    int var = 23;
    int* ptr_to_var = &var;
  
    cout << "Returning a Reference " << endl;
  
    cout << "Before :" << *ptr_to_var << endl; // display 23
  
    ptr_to_var = &ReturnReference();
  
    cout << "After :" << *ptr_to_var << endl; // display 42
  
    return 0;
}