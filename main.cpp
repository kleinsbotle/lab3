#include <iostream>
#include <string>

#include "Haff_coder.h"


using namespace std;





int main() {

   string str;
   cout << "Enter the message: " << endl;
   getline(cin, str);
   Haff_coder coder = Haff_coder(str);
   coder.Encode();
    return 0;
}