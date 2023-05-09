#include <iostream> 
#include <vector>

using namespace std;

int main(){
    vector<string> stooges {"larry", "mo", "curly"};
    vector<string> *vector_ptr {nullptr};

    vector_ptr = &stooges;

    cout << "First stooge: " << (*vector_ptr).at(0) << endl; // use params to ensure we dereference first 

    cout << "Stooges: ";
    for (auto stooge: *vector_ptr)
        cout << stooge << " ";
    cout << endl;

    cout << endl;
    return 0;
}