#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

using json = nlohmann::json;

class Config {
public:
    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(Config const&) = delete;
    Config& operator=(Config&&) = delete;

    static Config& instance();
    void initialize(const std::string& path);

    uint32_t get_memory_limit() const;
    uint32_t get_input_delay() const;
    uint32_t get_output_delay() const;
    uint32_t get_winding_delay() const;
    uint32_t get_shift_delay() const;

protected:
    Config() = default;
    ~Config() = default;

private:
    bool check_structure_(json& data);
    uint32_t memory_limit_, input_delay_, output_delay_,\
            winding_delay_, shift_delay_;
};

#endif