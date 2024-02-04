#include <iostream>
using namespace std;

/*
carpet cleaning service 
charges $30 per room 
sales tax is 6% 
estimates are valid for 30 days 

prompt use for number of rooms they want cleaned and provide estimate 
*/

int main(){
    cout << "Hello, welcome to Frank's Carpet cleaning service" << endl << endl;
    cout << "How many rooms would you like cleaned? " << endl;

    int number_of_rooms {0};
    cin >> number_of_rooms;

    const double price_per_room {30.0};
    const double sales_tax {0.06};
     
    cout <<"\nEstimate for carpet cleaning service" << endl;
    cout << "Number of rooms: " << number_of_rooms << endl;
    cout << "Price per room: $" << price_per_room << endl;
    cout << "Cost: $" << price_per_room * number_of_rooms << endl;
    cout << "Tax: $" << price_per_room * number_of_rooms * sales_tax << endl;
    cout << "===============================" << endl;

    cout << "Total estimate: $" << (price_per_room * number_of_rooms) + (price_per_room * number_of_rooms * sales_tax) << endl; 


    cout << endl;

    return 0;
}