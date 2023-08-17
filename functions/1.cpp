#include <iostream>
  
using namespace std;
  
int global_Var = 42;
  
// function to change pointer value
void changePointerValue(int* pp)
{
    pp = &global_Var;
}
  
int main()
{
    int var = 23;
    int* ptr_to_var = &var;
  
    cout << "Passing Pointer to function:" << endl;
  
    cout << "Before :" << *ptr_to_var << endl; // display 23
  
    changePointerValue(ptr_to_var);
  
    cout << "After :" << *ptr_to_var << endl; // display 23
  
    return 0;
}