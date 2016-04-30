
#include <cppassist/cmdline/ArgumentParser.h>

#include <iostream>


namespace cppassist
{


ArgumentParser::ArgumentParser()
{
}

ArgumentParser::~ArgumentParser()
{
}

void ArgumentParser::parse(int argc, char * argv[])
{
    for (int i=1; i<argc; i++) {
        // Get current and next argument
        std::string arg  = argv[i];
        std::string next = (i+1 < argc ? argv[i+1] : "");

        // Options with value (--option-name <value>)
        if (arg.find("--") == 0) {
            // Save value
            m_options[arg] = next;
            i++;
        }

        // Options without value (-option-name)
        else if (arg.find("-") == 0) {
            m_options[arg] = "true";
        }

        // Additional parameters
        else {
            m_params.push_back(arg);
        }
    }
}

std::map<std::string, std::string> ArgumentParser::options() const
{
    return m_options;
}

bool ArgumentParser::isSet(const std::string & option) const
{
    return m_options.count(option) > 0;
}

std::string ArgumentParser::value(const std::string & option) const
{
    if (isSet(option)) {
        return m_options.at(option);
    } else {
        return "";
    }
}

std::vector<std::string> ArgumentParser::params() const
{
    return m_params;
}

void ArgumentParser::print() const
{
    std::cout << "Options:" << std::endl;
    for (auto param : m_options) {
        std::string option = param.first;
        std::string value  = param.second;
        std::cout << "  " << option << " = " << value << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Parameters:" << std::endl;
    for (auto param : m_params) {
        std::cout << "  " << param << std::endl;
    }
    std::cout << std::endl;
}


} // namespace cppassist
