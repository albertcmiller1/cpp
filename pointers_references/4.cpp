#include <iostream> 

using namespace std;

int main(){

    int score {100};

    int *score_ptr {nullptr};   // initilize a pointer 

    score_ptr = &score;         // set the value of the pointer to the address of score

    cout << "the value of score      " << score << endl;        // value of score variable 
    cout << "the address of score    " << &score << endl;       // address of score 
    cout << "value of score_ptr      " << score_ptr << endl;    // value of score_ptr pointer (aka address of score)
    cout << "address of score_ptr    " << &score_ptr << endl;   // address of score_ptr pointer
    cout << "derefernce score_ptr    " << *score_ptr << endl;   // value of the address of score_ptr pointer 
}