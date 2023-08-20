#include<iostream> 
#include<memory> 

using namespace std;

int main(){
    auto ptr = std::make_unique<int[]>(10);
    for (int i = 0; i < 10; i += 1){
        ptr[i] = i * i;
    }
    cout << ptr[4] << endl;
    cout << ptr[7] << endl;
    return 0;
}