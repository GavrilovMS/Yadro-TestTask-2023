#include "config.hpp"

Config& Config::instance() {
    static Config instance;
    return instance;
}

void Config::initialize(const std::string& path) {
    std::ifstream f(path);
    json data = json::parse(f);
    f.close();
    if (!check_structure_(data)) {
        throw std::runtime_error("Config structure is not valid");
    }
    memory_limit_ = data["memory_limit"];
    input_delay_ = data["input_delay"];
    output_delay_ = data["output_delay"];
    winding_delay_ = data["winding_delay"];
    shift_delay_ = data["shift_delay"];
}

bool Config::check_structure_(json& data) {
    return data.contains("memory_limit") &&
        data.contains("input_delay") &&
        data.contains("output_delay") &&
        data.contains("winding_delay") &&
        data.contains("shift_delay");
}

uint32_t Config::get_memory_limit() const {
    return memory_limit_;
}

uint32_t Config::get_input_delay() const {
    return input_delay_;
}

uint32_t Config::get_output_delay() const {
    return output_delay_;
}

uint32_t Config::get_winding_delay() const {
    return winding_delay_;
}

uint32_t Config::get_shift_delay() const {
    return shift_delay_;
}