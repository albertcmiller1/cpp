#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_smart(int *a, int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main(){
    int x {100}, y {200}; 
    std::cout << "\nx: " << x << std::endl;
    std::cout << "\ny: " << y << std::endl;

    // swap(&x, &y);
    swap_smart(&x, &y);

    std::cout << "\nx: " << x << std::endl;
    std::cout << "\ny: " << y << std::endl;

    return 0;
}


