#include <iostream>
using namespace std;

int main(){
    ex1();
    ex2();
    return 0;
}

// pointers to constants 
        // > the data pointed to by the pointers is constant and cannot be changed
        // > the pointer itself can change and point somewhere else
void ex1(){
    int h {100};
    int l {65};

    const int *ptr {&h};
    // *ptr = 86; // ERROR
    ptr = &l;
}


// constant pointers 
//     > the data pointed to by the pointers can be changed
//     > the pointer itself cannot change and point shomewhere else
void ex2(){
    int h {100};
    int l {65};

    int *const ptr {&h}; 
    *ptr = 86; 
    // ptr = &l; // ERROR
}

void ex3(){
    int h {100};
    int l {65};

    const int *const ptr {&h}; 
    // *ptr = 86; // ERROR
    // ptr = &l; // ERROR
}