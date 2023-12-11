#include <gtest/gtest.h>

#include <fstream>

#include "file-tape.hpp"
#include "config.hpp"




TEST(FileTapeTest, ConstructorFromTxt) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");
    
    ASSERT_EQ(10, tape1.get_length());
    ASSERT_EQ(0, tape2.get_length()); // check for empty input
    
}

TEST(FileTapeTest, ConstructorWithSize) {
    FileTape tape1(10, "test-input-tape1.bin");
    FileTape tape2(0, "test-input-tape2.bin");

    ASSERT_EQ(10, tape1.get_length());
    ASSERT_EQ(0, tape2.get_length()); // check for empty input
}


TEST(FileTapeTest, Read) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");

    ASSERT_EQ(1, tape1.read());
    ASSERT_EQ(NULL, tape2.read()); // check for empty input
}

TEST(FileTapeTest, Write) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");

    tape1.write(11);
    tape2.write(11);
    ASSERT_EQ(11, tape1.read());
    ASSERT_EQ(NULL, tape2.read()); // check for empty input
}

TEST(FileTapeTest, ShiftLeft) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");

    tape1.shift_left();
    tape2.shift_left();
    ASSERT_EQ(2, tape1.read());
    ASSERT_EQ(NULL, tape2.read()); // check for empty input
}

TEST(FileTapeTest, ShiftRight) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");

    tape1.shift_left();
    tape2.shift_left();
    tape1.shift_right();
    tape2.shift_right();
    
    ASSERT_EQ(1, tape1.read());
    ASSERT_EQ(NULL, tape2.read()); // check for empty input
}


TEST(FileTapeTest, WindLeft) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");

    tape1.wind_left(1); //check for usual winding
    ASSERT_EQ(2, tape1.read());
    tape1.wind_left(9); //check for winding with out of bounds
    ASSERT_EQ(10, tape1.read());

    tape2.wind_left(1);
    ASSERT_EQ(NULL, tape2.read());
    tape2.wind_left(10);
    ASSERT_EQ(NULL, tape2.read());
}

TEST(FileTapeTest, WindRight) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");
    FileTape tape2("test-input2.txt", "test-input-tape2.bin");

    tape1.wind_left(10);
    tape2.wind_left(10);

    tape1.wind_right(1); //check for usual winding
    ASSERT_EQ(9, tape1.read());
    tape1.wind_right(9); //check for winding with out of bounds
    ASSERT_EQ(1, tape1.read());

    tape2.wind_right(1);
    ASSERT_EQ(NULL, tape2.read());
    tape2.wind_right(10);
    ASSERT_EQ(NULL, tape2.read());

}

TEST(FileTapeTest, CreateTxt) {
    FileTape tape1("test-input1.txt", "test-input-tape1.bin");

    tape1.shift_left();
    tape1.create_txt("test-txt.txt");
    std::ifstream txt_file("test-txt.txt", std::ios::in);

    int32_t temp;
    txt_file >> temp;

    ASSERT_EQ(1, temp);
    ASSERT_EQ(2, tape1.read());

}



int main(int argc, char **argv) {
    Config::instance().initialize("config.json");

    size_t test_length = 10;
    std::ofstream txt_file1("test-input1.txt", std::ios::out | std::ios::trunc);
    std::ofstream txt_file2("test-input2.txt", std::ios::out | std::ios::trunc);
    for (size_t i = 1; i < test_length+1; i++) {
        txt_file1 << i << ' ';
    }
    txt_file1.close();
    txt_file2.close();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}