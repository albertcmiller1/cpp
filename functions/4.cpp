#include <iostream>
  
using namespace std;
  
int gobal_var = 42;
  
// function to change Reference to pointer value
void changeReferenceValue(int*& pp)
{
    pp = &gobal_var;
}
  
int main()
{
    int var = 23;
    int* ptr_to_var = &var;
  
    cout << "Passing a Reference to a pointer to function" << endl;
  
    cout << "Before :" << *ptr_to_var << endl; // display 23
  
    changeReferenceValue(ptr_to_var);
  
    cout << "After :" << *ptr_to_var << endl; // display 42
  
    return 0;
}