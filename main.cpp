#include <iostream>
#include <string>

#include "Haff_coder.h"

int main() {

   std::string str;
   std::cout << "Enter the message: " << std::endl;
   getline(std::cin, str);
   Haff_coder coder = Haff_coder(str);
  /* std::cout << coder.Encode() << std::endl;
   coder.TablePrint();*/
  /* cout << "Enter the message to decode: " << endl;
   getline(cin, str);
   std::cout << coder.Decode(str);*/
  coder.FrequencyPrint();
  coder.TablePrint();
  std::cout << coder.Encode() << std::endl;
  coder.MemInfo();
    return 0;
}