#include <iostream> 

using namespace std; 

int age(18); // global variable 
int age2 = 19; 

int main(){
    // int age(16); // local variable will overwrite s
    cout << age << endl;
    cout << age2 << endl;

    return 0;
}


