#include <iostream>
using namespace std;

int main() {

    int num1; 
    int num2; 

    cout << "Enter an integer: ";
    cin >> num1;
    cout << "Enter another integer: ";
    cin >> num2;
    cout << "you entered: " << num1 << " and " << num2 << endl;
    cout << "these two numbers multiplied = " << num1 * num2 << endl;

    // interesting ...
    // if you enter two numbers after the first prompt, the code will still take both inputs. 

    return 0;
}