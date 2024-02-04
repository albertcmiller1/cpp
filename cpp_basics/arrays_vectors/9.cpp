
#include <iostream>
#include <array> 
using namespace std;


int main()
{

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    for (auto itr = arr.begin(); itr < arr.end(); itr++){
        cout << *itr << ' ';
    }
    cout << endl;

    for (auto itr = arr.begin() + 2; itr < arr.end(); itr++){
        cout << *itr << ' ';
    }
    cout << endl;

    for (auto itr = arr.rbegin(); itr < arr.rend(); itr++){
        cout << *itr << ' ';
    }
    cout << endl;
    return 0;
}