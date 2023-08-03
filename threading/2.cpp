// C++ program to demonstrate multithreading using three different callables.
#include <iostream>
#include <thread>
#include<unistd.h>  
using namespace std;

// A dummy function
void foo(int Z){
    for (int i = 0; i < Z; i++){
	    cout << "Thread using function pointer as callable\n";
    }
}

// Driver code
int main(){
    cout << "spinning up thread" << endl;

    // This thread is launched by using function pointer as callable
    thread th1(foo, 10);
    
    // Wait for thread t1 to finish
    // th1.join();
    // cout << "this should be after" << endl;

    while (true){
        sleep( 5 );  
        cout << "main function still working" << endl;
    }

    return 0;
}
