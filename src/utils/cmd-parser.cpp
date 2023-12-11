#include "cmd-parser.hpp"

CMDParser::CMDParser() : c_path_{""}, i_path_{""}, o_path_{""} {

}

void CMDParser::parse(int argc, char** argv) {
    for (size_t i = 1; i < argc-1; i++) {
        std::string temp(argv[i]);
        if (temp == "-c" && argv[i+1][0] != '-') {
            c_path_ = argv[i+1];
        }
        if (temp == "-i" && argv[i+1][0] != '-') {
            i_path_ = argv[i+1];
        }
        if (temp == "-o" && argv[i+1][0] != '-') {
            o_path_ = argv[i+1];
        }
    }
    if (!check_files_()) {
        throw std::runtime_error("invalid input arguments");
    } 
}

bool CMDParser::check_files_() {
    std::fstream c_file(c_path_);
    if(!c_file.is_open()) return false;

    std::fstream i_file(i_path_);
    if(!i_file.is_open()) return false;

    if(o_path_ == "") return false;

    return true;
}    
std::string CMDParser::get_input_path() const {
    return i_path_;
}

std::string CMDParser::get_output_path() const {
    return o_path_;
}

std::string CMDParser::get_config_path() const {
    return c_path_;
}