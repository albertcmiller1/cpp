# include <iostream> 
using namespace std; 

int main(){

    double high_temps[] {91.2, 88.32, 99.23, 101.21};
    cout << "\nThe first high temp is " << high_temps[0] << endl;
    high_temps[0] = 110.11;
    cout << "\nThe first high temp is now " << high_temps[0] << endl;

    return 0;
}