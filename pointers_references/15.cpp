#include <iostream>
using namespace std;

void display(vector<string> *v){
    (*v).at(0) = "poopy";
    
    for (auto str : *v)
        cout << str << " ";
    cout << endl;

}

int main(){

    vector<string> ppl {"mo", "chris", "albert"};
    display(&ppl);


    return 0;
}
