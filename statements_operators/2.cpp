#include <iostream> 
using namespace std;

int main() {

    int counter {10};
    int result {0};
    result = ++counter; // increment counter, then assign counter to result 
    cout << "counter is " << counter << endl;
    cout << "result is " << result << endl;

    cout << endl;

    counter = 10;
    result = 0;
    result = counter++; // assign counter to result, then increment counter 
    cout << "counter is " << counter << endl;
    cout << "result is " << result << endl;

    return 0;
}

