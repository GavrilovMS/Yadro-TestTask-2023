#ifndef TAPE_SORTER
#define TAPE_SORTER

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "file-tape.hpp"

class TapeSorter{
public:
    TapeSorter(size_t memory_limit);
    ~TapeSorter();

    void sort(FileTape& input_tape, FileTape& output_tape);

private:
    std::vector<std::shared_ptr<FileTape>> split_and_sort(FileTape& tape);
    void merge_(std::vector<std::shared_ptr<FileTape>>& tapes, FileTape& res_tape);
    void merge_two_tapes_(FileTape& tape2, FileTape& tape1, FileTape& res_tape);
    
    size_t mem_limit_;
};

#endif 