#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Haff_coder.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int n = RUN_ALL_TESTS();

    std::string str;
    std::cout << "Enter the message: " << std::endl;
    getline(std::cin, str);
    Haff_coder string = Haff_coder(str);
    string.FrequencyPrint();
    string.TablePrint();
    std::cout << string.Encode() << std::endl;
    string.MemInfo();
    std::cout << "Enter the message to decode: " << std::endl;
    getline(std::cin, str);
    std::cout << string.Decode(str);
    return 0;
}