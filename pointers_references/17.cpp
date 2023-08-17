#include <iostream>
 
using namespace std;
 
void no_reference(){
   vector<string> ppl {"albert", "mo", "chris"};

   for (auto s : ppl){
      s = "nerd";       // without a reference, "s" variable is a copy of each of the vector elements 
   }

   for (auto s : ppl){
      cout << s << endl;
   }
}

void reference(){
   vector<string> ppl {"albert", "mo", "chris"};

   for (auto &s : ppl){
      s = "nerd";
   }

   for (auto s : ppl){
      cout << s << endl;
   }
}



int main () {
   no_reference();
   cout << "\n";
   reference();

   return 0;
}