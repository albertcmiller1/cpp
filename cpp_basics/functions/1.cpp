#include <iostream>
using namespace std;
//https://www.geeksforgeeks.org/passing-reference-to-a-pointer-in-c/

int global_Var = 42;
  
// function to change pointer value
void changePointerValue(int* pp)
{
    // *pp = 69;               // this works÷
    pp = &global_Var;    // this doesnt
    cout << "test :" << *pp << endl;  // 23
}
// Moral: we can update the value a pointer is pointing to, but cant update the value of the address of the pointer (at least not in another function) 
// is this because the value of the pointer is a copy of the pointer? 
int main()
{
    int var = 23;
    int *ptr_to_var = &var;
  
    cout << "Passing Pointer to function:" << endl;
  
    cout << "Before :" << *ptr_to_var << endl; // 23
  
    changePointerValue(ptr_to_var);
  
    cout << "After :" << *ptr_to_var << endl;  // 23
  
    return 0;
}