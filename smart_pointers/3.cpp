#include<iostream> 
#include<memory> 

using namespace std;

// shared pointers can have multiple pointers pointing to the same memory 
// shared pointers use reference counting 

int main(){
    std::shared_ptr<int[]> ptr(new int[10]);

    auto ptr2 = ptr;

    cout << "Reference count: " << ptr2.use_count() << endl;


    // for (int i = 0; i < 10; i += 1){
    //     ptr[i] = i * i;
    // }
    // cout << ptr[4] << endl;
    // cout << ptr[7] << endl;
    // return 0;
}