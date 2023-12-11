#include <iostream>
#include <memory>

#include "cmd-parser.hpp"
#include "config.hpp"
#include "file-tape.hpp"
#include "tape-base.hpp"
#include "tape-sorter.hpp"

#include <spdlog/spdlog.h>

int main(int argc, char** argv){
    CMDParser cmd_parser;
    try {
        cmd_parser.parse(argc, argv);
        spdlog::info("Config: {}", cmd_parser.get_config_path());
        spdlog::info("Input-path: {}", cmd_parser.get_input_path());
        spdlog::info("Output-path: {}", cmd_parser.get_output_path());

        Config::instance().initialize(cmd_parser.get_config_path());
    } catch (std::exception& ex) {
        spdlog::critical("Execution error: {}", ex.what());
        return -1;
    }

    
    FileTape input_tape(cmd_parser.get_input_path(), "input-tape.bin");
    FileTape output_tape(input_tape.get_length(), "output-tape.bin");

    TapeSorter tape_sorter(Config::instance().get_memory_limit());
    tape_sorter.sort(input_tape, output_tape);

    output_tape.create_txt(cmd_parser.get_output_path());

    return 0;
}

