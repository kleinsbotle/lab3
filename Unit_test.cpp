//
// Created by efg on 08.04.19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Haff_coder.h"

using testing::Eq;


TEST(Encode, Test1){
    Haff_coder string = Haff_coder("To be, or not to be--that is the question:");
    EXPECT_EQ(string.GetTable()->GetSize(), string.GetFreqTable()->GetSize());
}

TEST(Encode, Test2){
    Haff_coder string = Haff_coder("To be, or not to be--that is the question:");
    EXPECT_EQ(string.Encode(), "11000100011101111111100110110011001001110101001010110110001110111111000100011010000111001101010011001001101000011110111100011101111110010101001110011010111010");
}

TEST(Encode, OneLetter){
    Haff_coder string = Haff_coder("A");
    EXPECT_EQ("1", string.Encode());
}

TEST(Encode, TwoLetters){
    Haff_coder string = Haff_coder("Ab");
    EXPECT_EQ("10", string.Encode());
}

TEST(Encode, SimilarLetters){
    Haff_coder string = Haff_coder("aaaaaaaaaa");
    EXPECT_EQ("1111111111", string.Encode());
}

TEST(Encode, EmptyString){
    try{
        Haff_coder string = Haff_coder("");
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("The string is empty"));
    }
}

TEST(Encode, Decode){
    Haff_coder string = Haff_coder("This is test string");
    EXPECT_EQ(string.Decode("0111110001001"), "sign");
}

TEST(Encode, Decode_WrongInput){
    Haff_coder string = Haff_coder("This is test string");
    try{
        string.Decode("1101101");
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("Wrong input"));
    }
}

TEST(Encode, Decode_One){
    Haff_coder string = Haff_coder("I disapprove of what you say, but I will defend to the death your right to say it");
    EXPECT_EQ(string.Decode("1010"), "a");
}

TEST(Encode, Decode_EmptyInput){
    Haff_coder string = Haff_coder("This is test string");
    try{
        string.Decode("");
    }
    catch(std::invalid_argument &err){
        EXPECT_THAT(std::string(err.what()), Eq("Wrong input"));
    }
}
