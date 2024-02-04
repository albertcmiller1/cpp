#include <iostream>
using namespace std;

int main(){

    int test_scores[5];

    // will print out random (junk)values which are currenlty stored in memory 

    cout << "the first test score at index 0: " << test_scores[0] << endl;
    cout << "the first test score at index 1: " << test_scores[1] << endl;
    cout << "the first test score at index 2: " << test_scores[2] << endl;
    cout << "the first test score at index 3: " << test_scores[3] << endl;
    cout << "the first test score at index 4: " << test_scores[4] << endl;

    cout << endl;
    int other_test_scores[5] {};

    // adding the {} will initilize all values to 0

    cout << "the first test score at index 0: " << other_test_scores[0] << endl;
    cout << "the first test score at index 1: " << other_test_scores[1] << endl;
    cout << "the first test score at index 2: " << other_test_scores[2] << endl;
    cout << "the first test score at index 3: " << other_test_scores[3] << endl;
    cout << "the first test score at index 4: " << other_test_scores[4] << endl;

    // this will print out the memory address of the first element in the array 
    cout << "notice what the value of the array name is: " << other_test_scores << endl;

    return 0;
}