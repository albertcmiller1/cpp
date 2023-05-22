#include <iostream>
using namespace std;


struct rect {
    float a;    // for height
    int b;      // for width

    rect(){
        a=10.58;
        b=4;
        cout<<"Area at default constructor is: "<<a*b<<endl;
    }

    rect(float x, int y){
        cout<<"Area is: "<<x*y;
    }
};


int main(){
    rect r1;
    float x;
    int y;
    cout<<"Enter height value: "<<endl;
    cin>>x;
    cout<<"Enter width value: "<<endl;
    cin>>y;
    rect(x,y);
}