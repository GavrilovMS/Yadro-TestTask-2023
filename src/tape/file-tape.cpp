#include "file-tape.hpp"

FileTape::FileTape(){
    is_deleted_ = true;
}

FileTape::~FileTape() {
    delete_tape();
}


FileTape::FileTape(const std::string& path, const std::string& tape_path) {
    create_from_txt(path, tape_path);
}

FileTape::FileTape(size_t size, const std::string& tape_path) : path_{tape_path}, is_deleted_{false}  {
    len_ = 0;
    cur_ = 0;
    file_.open(tape_path, std::ios::binary | std::ios::trunc | std::ios::out | std::ios::in);
    int32_t temp = 0;
    for (size_t i = 0; i < size; i++) {
        file_.write((char*)&temp , sizeof(temp));
        len_++;
    }

    file_.seekg(0, std::ios_base::beg);
}


void FileTape::create_from_txt(const std::string& path, const std::string& tape_path) {
    len_ = 0;
    cur_ = 0;
    is_deleted_ = false;
    path_ = tape_path;
    std::fstream txt_file(path, std::ios::in | std::ios::app);
    
    file_.open(tape_path, std::ios::binary | std::ios::trunc | std::ios::out | std::ios::in);

    for (int32_t temp; txt_file >> temp;) {
        file_.write((char*)&temp, sizeof(temp));
        len_++;
    }

    file_.seekg(0, std::ios_base::beg);
}

void FileTape::create_txt(const std::string& path) {
    if (is_deleted_) return;

    std::ofstream txt_file(path, std::ios::out | std::ios::trunc);
    file_.seekg(0, std::ios_base::beg);

    int32_t temp;

    for (size_t i = 0; i < len_; i++) {
        file_.read((char*)&temp, sizeof(temp));
        txt_file << temp << ' ';
    }

    file_.seekg(cur_ * sizeof(int32_t), std::ios_base::beg);
}

size_t FileTape::get_length() const {
    if (is_deleted_) return 0;
    return len_;
}

size_t FileTape::get_cur() const {
    if (is_deleted_) return 0;
    return cur_;
}

int32_t FileTape::read() const {
    if (len_ == 0 | is_deleted_) return NULL;
    int32_t res;
    file_.read((char*)&res, sizeof(res));
    file_.seekg(-sizeof(res), std::ios_base::cur);

    std::this_thread::sleep_for(std::chrono::milliseconds(Config::instance().get_output_delay()));
    return res;
}

void FileTape::write(const int32_t& data) {
    if (len_ == 0 | is_deleted_) return;
    file_.write((char*)&data, sizeof(data));
    file_.seekg(-sizeof(data), std::ios_base::cur);
    std::this_thread::sleep_for(std::chrono::milliseconds(Config::instance().get_input_delay()));
}

void FileTape::shift_left() {
    if (is_deleted_) return;
    if (cur_ == len_ - 1) return;
    cur_++;
    file_.seekg(sizeof(int32_t), std::ios_base::cur);
    std::this_thread::sleep_for(std::chrono::milliseconds(Config::instance().get_shift_delay()));
}


void FileTape::shift_right() {

    if (cur_ == 0 | is_deleted_) return;
    cur_--;
    file_.seekg(-sizeof(int32_t), std::ios_base::cur);
    std::this_thread::sleep_for(std::chrono::milliseconds(Config::instance().get_shift_delay()));
}

void FileTape::wind_left(size_t len) {
    if (is_deleted_) return;
    if(cur_ + len > len_ - 1) {
        cur_ = len_ - 1;
        file_.seekg(cur_ * sizeof(int32_t), std::ios_base::beg);
        return;
    }
    cur_ += len;
    file_.seekg(sizeof(int32_t) * len, std::ios_base::cur);
    std::this_thread::sleep_for(std::chrono::milliseconds(Config::instance().get_winding_delay()));
}

void FileTape::wind_right(size_t len) {
    if (is_deleted_) return;
    if(int(cur_ - len) < 0) {
        cur_ = 0;
        file_.seekg(0, std::ios_base::beg);
        return;
    }
    cur_ -= len;
    file_.seekg(-sizeof(int32_t) * len, std::ios_base::cur);
    std::this_thread::sleep_for(std::chrono::milliseconds(Config::instance().get_winding_delay()));
}

void FileTape::delete_tape() {
    if (is_deleted_) return;
    std::remove(path_.c_str());
    is_deleted_ = true;
}