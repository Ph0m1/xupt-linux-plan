#ifndef CLI_COMMAND_HPP
#define CLI_COMMAND_HPP
#include <string>
#include <vector>

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
     virtual void execute(const std::vector<std::string> &args) = 0;
    virtual void help() = 0;
    virtual void help(const std::vector<std::string> &args) = 0;
    
};

//class CliCommand;

#endif