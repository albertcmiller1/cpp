#include <iostream>
#include <span> 
#include <vector> 

using namespace std;

// spand is a new C++ feature in the '20 realease 
// it means we are not copying anything, we are only looking into it 
// does that mean when we use normal functions, we copy the value of the num every time? even when we pass as a reference? 

void print_subvector(std::span<int> span){

    for (auto n : span){
        cout << n << " ";
    }
    cout << endl;
}

int main(){
    vector<int> arr = {44, 22, 66, 55, 88};
    print_subvector(arr);
    print_subvector(std::span(arr.begin(), 2));
    print_subvector(std::span(arr.begin()+2, 2));
    return 0;
}