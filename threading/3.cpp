// C++ program to demonstrate multithreading using three different callables.
#include <iostream>
#include <thread>
#include<unistd.h>  
using namespace std;

// A dummy function
void foo(){
    while (true){
        sleep( 5 );  
        cout << "THREAD still up and running\n" << endl;
    }
}

// Driver code
int main(){
    cout << "spinning up thread" << endl;

    // This thread is launched by using function pointer as callable
    thread th1(foo);

    
    // Wait for thread t1 to finish
    // th1.join();
    // cout << "this should be after" << endl;


    cout << "main function done working\n" << endl;

    while (true){
        sleep( 1 );  
        cout << "listening for incoming requests\n" << endl;
    }


    return 0;
}
