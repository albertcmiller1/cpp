#include <iostream>
using namespace std; 

int main() {
    // arrays havent been initialized yet 
    int test_scores [5];
    const int days_in_year {365};
    double high_temperatures [days_in_year];

    int test_scores_1 [5] {100, 95}; // init to 100,95 and remaining to 0
   
    const int days_in_year_1 {365};
    double high_temperatures_1 [days_in_year] {0}; // initalize all to 0

    int another_array [] {1,2,3,4,5}; // size automatically calculated 

    cout << "first score in test_scores_1 " << test_scores_1[0] << endl;

    return 0;
}
