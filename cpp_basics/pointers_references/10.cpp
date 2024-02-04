#include <iostream>
using namespace std;

int main(){
    int scores[] = {100, 200, 300};
    int *scores_ptr = scores;

    cout << "value of scores: " << scores << endl;
    cout << "value of scores ptr: " << scores_ptr << endl;

    cout << "Array subscript notation: " << endl;
    cout << scores[0] << endl;
    cout << scores[1] << endl;
    cout << scores[2] << endl;

    cout << "Pointer subscript notation: " << endl;
    cout << scores_ptr[0] << endl;
    cout << scores_ptr[1] << endl;
    cout << scores_ptr[2] << endl;

    cout << "Pointer offset notation: " << endl;
    cout << *scores_ptr << endl;
    cout << *(scores_ptr+1) << endl;
    cout << *(scores_ptr+2) << endl;
    
    cout << "Array offset notation: " << endl;
    cout << *scores << endl;
    cout << *(scores+1) << endl;
    cout << *(scores+2) << endl;
}