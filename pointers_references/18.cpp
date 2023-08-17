#include <iostream>
 
using namespace std;
 

void reference(vector<string> &ppl){
   for (auto &s : ppl){
      s = "nerd";
   }
}


void no_reference(vector<string> &ppl){
   for (auto s : ppl){
      s = "nerd";
   }
}

int main () {
   vector<string> ppl {"albert", "mo", "chris"};
   // reference(ppl);
   no_reference(ppl);
   // reference({"albert", "mo", "chris"}); // Error: cant reference R-Vlaue 

   for (auto s : ppl){
      cout << s << endl;
   }
   return 0;
}