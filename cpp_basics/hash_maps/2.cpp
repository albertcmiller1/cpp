#include <iostream>
#include <unordered_map>
#include <typeinfo>
using namespace std;

int main()
{
    vector<int> arr = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5};
    std::unordered_map<int, int> m = {};

    for (auto v: arr){
        if (m.find(v) != m.end()) m[v]++;
        else m[v] = 1;
    }
 
    for (auto x: m)
        cout << x.first << " -> " << x.second << endl;

    return 0;
}