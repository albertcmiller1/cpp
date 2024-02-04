#include <iostream> 

using namespace std;

int main(){

    double high_temp {100.7};
    double low_temp {37.4};
    double *temp_ptr {&high_temp};

    cout << *temp_ptr << endl;  // 100.7
    temp_ptr = &low_temp;
    cout << *temp_ptr << endl;  // 37.4
}