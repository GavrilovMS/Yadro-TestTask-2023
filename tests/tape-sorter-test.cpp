#include <gtest/gtest.h>

#include <fstream>

#include "tape-sorter.hpp"
#include "file-tape.hpp"
#include "config.hpp"

bool is_sorted(FileTape& output) {
    if (output.get_length() < 2) return true;
    output.wind_right(output.get_length());

    bool is_sorted = true;
    for (size_t i = 0; i < output.get_length() - 1; i++) {
        int32_t cur = output.read();
        output.shift_left();
        int32_t next = output.read();
        if (cur > next) {
            return false;
        }
    }
    return true;
}
TEST(TapeSorterTest, EmptyInput) { 
    FileTape tape("test-input-empty.txt", "test-input-empty-tape.bin");
    FileTape output(tape.get_length(), "test-output-empty-tape.bin");
    TapeSorter tape_sorter(Config::instance().get_memory_limit());
    tape_sorter.sort(tape, output);
    output.wind_right(output.get_length());

    ASSERT_EQ(true, is_sorted(output));
    output.create_txt("test-output-empty.txt");
}

TEST(TapeSorterTest, InputLessLimit) {
    FileTape tape("test-input-less-limit.txt", "test-input-less-limit-tape.bin");
    FileTape output(tape.get_length(), "test-output-less-limit-tape.bin");
    TapeSorter tape_sorter(Config::instance().get_memory_limit());
    tape_sorter.sort(tape, output);

    ASSERT_EQ(true, is_sorted(output));
    output.create_txt("test-output-less-limit.txt");
}

TEST(TapeSorterTest, InputEqLimit) {
    FileTape tape("test-input-eq-limit.txt", "test-input-eq-limit-tape.bin");
    FileTape output(tape.get_length(), "test-output-eq-limit-tape.bin");
    TapeSorter tape_sorter(Config::instance().get_memory_limit());
    tape_sorter.sort(tape, output);

    ASSERT_EQ(true, is_sorted(output));
    output.create_txt("test-output-eq-limit.txt");
}

TEST(TapeSorterTest, InputMoreLimit) {
    FileTape tape("test-input-more-limit.txt", "test-input-more-limit-tape.bin");
    FileTape output(tape.get_length(), "test-output-more-limit-tape.bin");
    TapeSorter tape_sorter(Config::instance().get_memory_limit());
    tape_sorter.sort(tape, output);

    ASSERT_EQ(true, is_sorted(output));
    output.create_txt("test-output-more-limit.txt");
}

TEST(TapeSorterTest, InputHigh) {
    FileTape tape("test-input-high.txt", "test-input-high-tape.bin");
    FileTape output(tape.get_length(), "test-output-high-tape.bin");
    TapeSorter tape_sorter(Config::instance().get_memory_limit());
    tape_sorter.sort(tape, output);

    ASSERT_EQ(true, is_sorted(output));
    output.create_txt("test-output-high.txt");
}

int main(int argc, char **argv) {
    Config::instance().initialize("config.json");

    size_t test_length = 1;
    std::ofstream txt_file1("test-input-empty.txt", std::ios::out | std::ios::trunc);
    std::ofstream txt_file2("test-input-less-limit.txt", std::ios::out | std::ios::trunc);
    std::ofstream txt_file3("test-input-eq-limit.txt", std::ios::out | std::ios::trunc);
    std::ofstream txt_file4("test-input-more-limit.txt", std::ios::out | std::ios::trunc);
    std::ofstream txt_file5("test-input-high.txt", std::ios::out | std::ios::trunc);

    int32_t limit = Config::instance().get_memory_limit() / sizeof(int32_t);

    for (size_t i = limit - 1; i > 0; i--) {
        txt_file2 << i << ' ';
    }
    for (size_t i = limit; i > 0; i--) {
        txt_file3 << i << ' ';
    }
    for (size_t i = limit+1; i > 0; i--) {
        txt_file4 << i << ' ';
    }
    for (size_t i = limit*10; i > 0; i--) {
        txt_file5 << i << ' ';
    }

    txt_file1.close();
    txt_file2.close();
    txt_file3.close();
    txt_file4.close();
    txt_file5.close();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}