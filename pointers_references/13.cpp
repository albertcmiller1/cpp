#include <iostream>
using namespace std;

void double_me(int *int_ptr){
    *int_ptr *= 2;
}

int main(){
    int value {10};             // on the stack
    int *int_ptr {nullptr};     // on the stack

    double_me(&value);
    std::cout << value << std::endl;

    int_ptr = &value;
    double_me(int_ptr);
    std::cout << value << std::endl;
    return 0;
}


