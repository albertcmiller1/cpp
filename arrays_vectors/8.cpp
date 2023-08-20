
#include <iostream>
#include <vector> 
using namespace std;

vector<int> doit(vector<int> *v, int new_val){

    for (int i=0; i<v->size(); i++){
        if (new_val > v->at(i)){
            v->insert(v->begin() + i, new_val);
        }
    }

    // for (auto i : *v){
    //     if (new_val > i){
    //     }
    // }
    return *v;
}


int main()
{
    vector<int> v {NULL};


    doit(&v, 50);
    doit(&v, 10);
    doit(&v, 20);
    doit(&v, 40);
    doit(&v, 30);
    // v = doit(v);


    // print
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}