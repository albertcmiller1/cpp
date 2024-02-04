#include <iostream> 

using namespace std;

int main(){

    int score{10};
    int *score_ptr {&score};   // initilize a pointer 

    cout << "derefernce score_ptr " << *score_ptr << endl;   // value of the address of score_ptr pointer 
    *score_ptr = 200; // update the value of what the pointer is pointing at by dereferencing at the same time 

    cout << *score_ptr << endl; 
    cout << score << endl; 
}