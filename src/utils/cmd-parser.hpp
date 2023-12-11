#ifndef CMD_PARSER
#define CMD_PARSER

#include <string>
#include <fstream>

class CMDParser{
public:

    CMDParser();
    ~CMDParser() = default;

    void parse(int argc, char** argv);

    std::string get_input_path() const;
    std::string get_output_path() const;
    std::string get_config_path() const;

private:
    bool check_files_();
    std::string i_path_, o_path_, c_path_;
};

#endif // !CMD_PARSER
