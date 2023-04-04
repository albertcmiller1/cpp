#include <iostream> 
using namespace std;

int main(){
    cout << (100 == 100) << endl;
    cout << (100 != 100) << endl;
    cout << boolalpha;
    cout << (100 == 100) << endl;
    cout << noboolalpha;
    cout << (100 == 100) << endl;
}