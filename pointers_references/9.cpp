#include <iostream> 
#include <vector>

using namespace std;

int main(){
    int *int_ptr {nullptr};
    int_ptr = new int;          // allocate an integer on the heap 
    cout << int_ptr << endl;    // random address
    cout << *int_ptr << endl;   // garbage 

    *int_ptr = 100;
    cout << *int_ptr << endl;

    delete int_ptr;
}