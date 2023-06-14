#include <iostream>
using namespace std;

void display(vector<string> *v){
    (*v).at(0) = "poopy";
    for (auto str : *v)
        cout << str << " ";
    cout << endl;
}


void display_other(int *arr, int sentinel){
    while (*arr != sentinel)
        cout << *arr++ << " ";
    cout << endl;
}

int main(){

    vector<string> ppl {"mo", "chris", "albert"};
    display(&ppl);


    int scores[] {100, 200, 300, -1};
    display_other(scores, -1);

    return 0;
}
