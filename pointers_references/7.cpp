#include <iostream> 

using namespace std;

int main(){

    string name = "Frank";
    string *str_ptr = &name;

    cout << *str_ptr << endl;
    name = "James";
    cout << *str_ptr << endl;
}