#include <iostream> 
using namespace std;

int main() {

    int counter {10};
    int result {0};
    result = ++counter; // do the ++ before assignment 
    cout << "counter is " << counter << endl;
    cout << "result is " << result << endl;

    cout << endl;

    counter = 10;
    result = 0;
    result = counter++; // do the ++ after assignment 
    cout << "counter is " << counter << endl;
    cout << "result is " << result << endl;

    return 0;
}

