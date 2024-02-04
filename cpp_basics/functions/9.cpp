#include <iostream>
#include <array> 
using namespace std;

// FUNCTION TEMPLATES SPECIALIZATION 
void print_array(auto arr)
{
    for (auto n : arr){
        cout << n << ' ' << endl;
    }
}

template<>
void print_array(std::array<int, 3> arr){
    cout << "printing from our specialization\n";
}

int main()
{
    std::array<int, 3> int_array = {4, 5, 6};
    std::array<float, 3> float_array = {9.1f, 10.0f, 11.5f};

    print_array(int_array);     // printing from our specialization
    print_array(float_array);   // 9.1 10 11.5 
    return 0;
}