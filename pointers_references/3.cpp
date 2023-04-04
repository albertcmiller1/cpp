#include <iostream> 

using namespace std;

int main(){

    int score{10};
    double high_temp{100.7};

    int *score_ptr {nullptr};

    score_ptr = &score; // OK

    // score_ptr = &high_temp // compiler error: must be similar type
}