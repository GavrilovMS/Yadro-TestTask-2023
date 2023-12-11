#ifndef FILE_TAPE_H
#define FILE_TAPE_H

#include "tape-base.hpp"
#include "config.hpp"

#include <fstream>
#include <string>
#include <chrono>
#include <thread>


class FileTape : public TapeBase<int32_t>{
public:
    FileTape();
    FileTape(const std::string& path, const std::string& tape_path);
    FileTape(const size_t size, const std::string& tape_path);

    FileTape(const FileTape& ref) = delete;
    FileTape& operator=(FileTape const& ref) = delete;
    FileTape(FileTape&& ref) = delete;
    FileTape& operator=(FileTape&& ref) = delete;

    ~FileTape();

    void create_from_txt(const std::string& path, const std::string& tape_path);
    void create_txt(const std::string& path);

    size_t get_length() const override;
    size_t get_cur() const override;
    int32_t read() const override;
    void write(const int32_t& data) override;

    void shift_left() override;
    void shift_right() override;
    void wind_left(size_t len) override;
    void wind_right(size_t len) override;

    void delete_tape();
private:
    mutable std::fstream file_;

    bool is_deleted_;
    std::string path_;
};
#endif