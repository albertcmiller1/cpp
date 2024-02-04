#include <iostream> 
using namespace std;

int main(){

    char vowels[] {'a', 'e', 'i', 'o', 'u'}; // will auto calculate len to be 5
    cout << "the first vowel is " << vowels[0] << endl;
    cout << "input a new vowl to array: " << endl;

    cin >> vowels[5]; // this should crash the program 
    cout << "the new vowel is " << vowels[5] << endl; // dont do this .. but its bad practice and gives warnings 

    return 0;
}