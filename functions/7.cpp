#include <iostream>
#include <array> 

using namespace std;
  
void print_array(std::array<int, 4> arr)
{
    for (auto n : arr){
        cout << n << ' ' << endl;
    }
}

void print_array(std::array<float, 4> arr)
{
    for (auto n : arr){
        cout << n << ' ' << endl;
    }
}
  
int main()
{
    std::array<int, 4> int_array = {4, 5, 6, 7};
    std::array<float, 4> float_array = {9.1f, 10.0f, 11.5f, 12.67f};
    // Function overloading 
    print_array(int_array);
    print_array(float_array);
  
    return 0;
}