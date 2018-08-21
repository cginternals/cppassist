
#pragma once


#include <string>
#include <vector>
#include <map>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Command line arguments parser
*
*    Can be used to parse the arguments from the command line.
*    The following command line syntax is assumed:
*
*    `<executable> [--<option> <value>]* [-<option>]* [<param>]*`
*
*    `<executable>`:
*      The first argument is assumed to be the current executable name.
*
*    `--<option>`:
*      Options with two slashes (`--`) must be followed by a value.
*
*    `-<option>`:
*      Options with a single slash (`-`) do not have a value. If present, their value is set to `true`.
*
*    `<param>`:
*      All other arguments found in the command line are assumed to be additional parameters
*      and are added to the parameter list.
*/
class CPPASSIST_API ArgumentParser
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ArgumentParser();

    /**
    *  @brief
    *    Destructor
    */
    ~ArgumentParser();

    /**
    *  @brief
    *    Parse command line
    *
    *  @param[in] argc
    *    Number of arguments
    *  @param[in] argv
    *    List of arguments
    */
    void parse(int argc, char * argv[]);

    /**
    *  @brief
    *    Get options
    *
    *  @return
    *    Options (key->value)
    *
    *  @remark
    *    Options without values (single "-") have the value `true` if set.
    */
    const std::map<std::string, std::string> & options() const;

    /**
    *  @brief
    *    Check if option is set
    *
    *  @param[in] option
    *    Name of option (e.g., "-v")
    *
    *  @return
    *    `true` if option is set, else `false`
    */
    bool isSet(const std::string & option) const;

    /**
    *  @brief
    *    Get option value
    *
    *  @param[in] option
    *    Name of option (e.g., "--v")
    *  @param[in] defaultValue
    *    Default value returned if option is not set
    *
    *  @return
    *    Value of the option or defaultValue if the option is not set
    */
    std::string value(const std::string & option, const std::string & defaultValue = "") const;

    /**
    *  @brief
    *    Get option value
    *
    *  @param[in] option
    *    Name of option (e.g., "--v")
    *  @param[in] defaultValue
    *    Default value returned if option is not set
    *
    *  @return
    *    Value of the option or defaultValue if the option is not set
    */
    const std::string & value(const std::string & option, std::string & defaultValue) const;

    /**
    *  @brief
    *    Get option value converted to specific data type
    *
    *  @param[in] option
    *    Name of option (e.g., "--v")
    *  @param[in] defaultValue
    *    Default value returned if option is not set
    *
    *  @return
    *    Value of the option
    *
    *  @remark
    *    Uses string::fromString() to convert to specified type
    */
    template <typename T>
    T value(const std::string & option, const T & defaultValue = T()) const;

    /**
    *  @brief
    *    Get additional parameters
    *
    *  @return
    *    Additional parameters
    */
    const std::vector<std::string> & params() const;

    /**
    *  @brief
    *    Print command line parameters to console
    */
    void print() const;


private:
    std::map<std::string, std::string> m_options; ///< Map (key->value) of options
    std::vector<std::string>           m_params;  ///< Additional parameters (e.g., file or object list)
};


} // namespace cppassist


#include <cppassist/cmdline/ArgumentParser.inl>
