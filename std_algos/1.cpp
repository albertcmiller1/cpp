#include <iostream>
#include <array>
#include <algorithm>
// https://en.cppreference.com/w/cpp/algorithm/sort
using namespace std;

void print(auto arr){
    for (auto n : arr){
        cout << n << " ";
    }
    cout << endl;
}

int main(){
    array<int, 5> arr = {44, 22, 66, 55, 88};
    print(arr);
    // std::sort(arr.begin(), arr.end());
    std::ranges::sort(arr);
    print(arr);
    return 0;
}