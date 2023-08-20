#include <iostream>
#include <array> 
using namespace std;

// FUNCTION TEMPLATES
  
template<typename T> 
void print_array(T arr)
{
    for (auto n : arr){
        cout << n << ' ' << endl;
    }
}

// only availbale in C++20. this makes a template behind the scene 
void print_array_2(auto arr)
{
    for (auto n : arr){
        cout << n << ' ' << endl;
    }
}

int main()
{
    std::array<int, 4> int_array = {4, 5, 6, 7};
    std::array<float, 4> float_array = {9.1f, 10.0f, 11.5f, 12.67f};
    // print_array<std::array<int, 4>>(int_array);
    // print_array<std::array<float, 4>>(float_array);
    print_array(int_array);
    print_array(float_array);
    cout << endl;
    print_array_2(int_array);
    print_array_2(float_array);
    return 0;
}