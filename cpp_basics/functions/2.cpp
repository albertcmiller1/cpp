#include <iostream>
using namespace std;
  
int global_var = 42;
// function to change pointer to pointer value
void changePointerValue(int** ptr_ptr)
{
    *ptr_ptr = &global_var;
}
  
int main()
{
    int var = 23;
    int* pointer_to_var = &var;
  
    cout << "Passing a pointer to a pointer to function " << endl;
  
    cout << "Before :" << *pointer_to_var << endl; // display 23
  
    changePointerValue(&pointer_to_var);
  
    cout << "After :" << *pointer_to_var << endl; // display 42
  
    return 0;
}