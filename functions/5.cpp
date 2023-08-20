#include <iostream>
  
using namespace std;
  
int global_var = 42;
  
// function to return a pointer
int* returnPointerValue()
{
    return &global_var;
}
  
int main()
{
    int var = 23;
    int *ptr_to_var = &var;
  
    cout << "Return a pointer from a function " << endl;
  
    cout << "Before :" << *ptr_to_var << endl; // 23
  
    ptr_to_var = returnPointerValue();
  
    cout << "After :" << *ptr_to_var << endl;   // 42
    cout << "var after :" << var << endl;       // 23
  
    return 0;
}