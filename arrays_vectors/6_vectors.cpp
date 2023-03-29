#include <iostream> 
#include <vector> 
using namespace std;

int main(){
    vector <char> vowels;
    vector <int> test_scores; // initilze an empty vector 
    vector <int> other_test_scores (10); // create a vector with 10 empty spots 
    vector <int> scores {100, 98, 89}; // initilize a vector with these 3 values 

    vector <double> high_temps (30, 80.0); // initilize a vector with 30 spots all initilized to be 80.0
    vector <double> other_high_temps (30); // initilize a vector with 30 spots all initilized to be 0

    // two ways to access 

    cout << "high temps at pos 0: " << high_temps[0] << endl;
    cout << "high temps at pos 2: " << high_temps.at(2) << endl;
    cout << endl;

    // vector.size()
    cout << "there are " << high_temps.size() << " elements in high_temps" << endl;

    cout << endl;
    // can append to end with method) vector.push_back()
    scores.push_back(55);
    cout << "scores at pos 3: " << scores.at(3) << endl;
    cout << "scores at pos 5: " << scores.at(5) << endl; // will give error: terminating with uncaught exception of type std::out_of_range: vector

    return 0;
}