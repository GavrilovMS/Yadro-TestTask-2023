#include "tape-sorter.hpp"

TapeSorter::TapeSorter(size_t memory_limit): mem_limit_{memory_limit} {
    std::filesystem::create_directory("tmp");
}

TapeSorter::~TapeSorter() {
    std::filesystem::remove("tmp");
}
void TapeSorter::sort(FileTape& input_tape, FileTape& output_tape) {
    if (input_tape.get_length() < 2) return;
    spdlog::info("Spliting and sorting tapes...");
    std::vector<std::shared_ptr<FileTape>> temp_tapes = split_and_sort(input_tape);
    spdlog::info("Merging tapes...");
    merge_(temp_tapes, output_tape);
    spdlog::info("Done");
}

std::vector<std::shared_ptr<FileTape>> TapeSorter::split_and_sort(FileTape& tape) {
    size_t len = mem_limit_/ 4;
    tape.wind_right(tape.get_length());

    size_t num = tape.get_length() / (mem_limit_ / sizeof(int32_t));
    if (tape.get_length() % (mem_limit_ / sizeof(int32_t)) != 0) num++;

    std::vector<std::shared_ptr<FileTape>> res;
    res.reserve(num);

    size_t cur = 0;
    while(cur != num) {
        //length of the sub-tape
        size_t temp_len;

        if (tape.get_length() - tape.get_cur() > len) {
            temp_len = len;
        } else {
            temp_len = tape.get_length() - tape.get_cur();
        }
        
        //reading sub-tape data
        std::vector<int32_t> data;
        data.reserve(temp_len);
        size_t next = tape.get_cur() + temp_len;
    
        while(tape.get_cur() < next) {
            uint32_t temp = tape.read();
            data.emplace_back(temp);

            if (tape.get_cur() == tape.get_length() -1 ) break;

            tape.shift_left();
        }

        //sort data
        std::sort(data.begin(), data.end());

        //create sub-tape
        std::shared_ptr<FileTape> temp_tape(new FileTape{data.size(), "tmp/tmp" + std::to_string(cur) + ".bin"});
        for (auto& it: data) {
            temp_tape->write(it);
            temp_tape->shift_left();
        }
        //save sub-tape
        res.emplace_back(temp_tape);
        cur++;
    }

    return res;
}


void TapeSorter::merge_(std::vector<std::shared_ptr<FileTape>>& tapes, FileTape& res_tape) {
    size_t i = 0;
    while (tapes.size() > 2) {
        size_t sz = tapes.size();
        size_t l1 = tapes[sz-1]->get_length();
        size_t l2 = tapes[sz-2]->get_length();
        size_t l3 = tapes[sz-3]->get_length();
        if (l1 > l2+l3) {
            std::shared_ptr<FileTape> res(new FileTape{l2+l3, "tmp/merged" + std::to_string(i++) + ".bin"});
            merge_two_tapes_(*tapes[sz-3], *tapes[sz-2], *res);
            std::shared_ptr<FileTape> temp = tapes[sz-1];
            tapes.erase(tapes.end()-3, tapes.end());
            tapes.push_back(res);
            tapes.push_back(temp);
        } else {
            
            std::shared_ptr<FileTape> res(new FileTape{l1+l2, "tmp/merged" + std::to_string(i++) + ".bin"});
            merge_two_tapes_(*tapes[sz-2], *tapes[sz-1], *res);
            tapes.erase(tapes.end()-2, tapes.end());
            tapes.push_back(res);
        }
        
    }
    if (tapes.size() == 2) {
            merge_two_tapes_(*tapes[0], *tapes[1], res_tape);
            return;
    }
    if (tapes.size() == 1) {
        tapes[0]->wind_right(tapes[0]->get_length());
        res_tape.wind_right(res_tape.get_length());
        for (size_t i = 0; i < res_tape.get_length(); i++) {
            res_tape.write(tapes[0]->read());
            res_tape.shift_left();
            tapes[0]->shift_left();
        }
    }
}

void TapeSorter::merge_two_tapes_(FileTape& tape2, FileTape& tape1, FileTape& res_tape) {
    if (res_tape.get_length() != tape1.get_length() + tape2.get_length()) return;
    tape1.wind_right(tape1.get_length());
    tape2.wind_right(tape2.get_length());
    res_tape.wind_right(res_tape.get_length());
    bool is_tape1_end = false;
    bool is_tape2_end = false;

    for (size_t i = 0; i < res_tape.get_length(); i++) {
        
        if (!is_tape1_end && !is_tape2_end) {
            int32_t temp1 = tape1.read();
            int32_t temp2 = tape2.read();
            if (temp1 > temp2) {
                res_tape.write(temp2);
                if (tape2.get_length() - 1 == tape2.get_cur()) {
                    is_tape2_end = true;
                }
                tape2.shift_left();
            } else {
                res_tape.write(temp1);
                if (tape1.get_length() - 1 == tape1.get_cur()) {
                    is_tape1_end = true;
                }
                tape1.shift_left();
            }
            res_tape.shift_left();
            continue;
        }

        if (!is_tape1_end && is_tape2_end) {
            int32_t temp1 = tape1.read();
            res_tape.write(temp1);
            if (tape1.get_length() - 1 == tape1.get_cur()) {
                is_tape1_end = true;
            }
            tape1.shift_left();
            res_tape.shift_left();
            continue;
        }
        
        if (is_tape1_end && !is_tape2_end) {
            int32_t temp2 = tape2.read();
            res_tape.write(temp2);
            if (tape2.get_length() - 1 == tape2.get_cur()) {
                is_tape2_end = true;
            }
            tape2.shift_left();
            res_tape.shift_left();
            continue;
        }
    }
}