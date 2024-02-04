#include <iostream>
#include <unordered_map>
#include <typeinfo>
using namespace std;

template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    // this & isnt really needed? why is it added? 
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main()
{
    std::unordered_map<int, char> m = {
        {1, 'A'},
        {2, 'B'},
        {3, 'C'}
    };

    m.insert({4, 6});
    m[5] = 'E';


    auto it = m.find(3); //returns a pointer to the location of the value found  
    auto end = m.end(); 
    // std::cout << typeid(it).name() << std::endl; // hash map iterator 

    std::cout << (*it).first << "-->" << (*it).second << std::endl;

    for (auto it = m.begin(); it != m.end(); ++it)
        cout << it->first << " = " << it->second << endl;

    // print_map(m);
 
    return 0;
}