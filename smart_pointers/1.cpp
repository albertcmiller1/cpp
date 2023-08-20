#include<iostream> 
#include<memory> 

using namespace std;

// unique pointers relase the memeory its using when the ptr goes out of scope 
// "unique" refers to the idea the the data the pointer is pointing to will only be accessed by this one pointer and not shared by multiple pointers 
// unique pointers do not slow the program down 

int main(){
    std::unique_ptr<int[]> ptr(new int[10]);
    for (int i = 0; i < 10; i += 1){
        ptr[i] = i * i;
    }
    cout << ptr[4] << endl;
    cout << ptr[7] << endl;
    return 0;
}