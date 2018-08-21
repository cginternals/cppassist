
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Command line parameter
*
*    A command line parameter is a stand-alone value that is specified
*    on the command line. For example, a filename at the end of the
*    command line can be required as a parameter.
*
*    Example:
*      `myapp <input> [<output>]`
*
*    @code
*      CommandLineParameter paramInput(
*          "input",
*          CommandLineParameter::NonOptional);
*
*      CommandLineParameter paramOutput(
*          "output",
*          CommandLineParameter::Optional);
*    @endcode
*/
class CPPASSIST_API CommandLineParameter
{
public:
    /**
    *  @brief
    *    State whether or not a parameter is optional
    */
    enum OptionalState
    {
        NonOptional = 0,
        Optional = 1
    };


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Parameter name (e.g., "filename")
    *  @param[in] optional
    *    Optional-state
    */
    CommandLineParameter(const std::string & name, OptionalState optional = Optional);

    /**
    *  @brief
    *    Destructor
    */
    ~CommandLineParameter();

    /**
    *  @brief
    *    Get parameter name
    *
    *  @return
    *    Parameter name (e.g., "filename")
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set parameter name
    *
    *  @param[in] name
    *    Parameter name (e.g., "filename")
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Check optional-flag
    *
    *  @return
    *    `true` if optional, else `false`
    */
    bool isOptional() const;

    /**
    *  @brief
    *    Check optional-flag
    *
    *  @return
    *    Optional-state
    */
    OptionalState optional() const;

    /**
    *  @brief
    *    Set optional-flag
    *
    *  @param[in] optional
    *    Optional-state
    */
    void setOptional(OptionalState optional);

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Parameter value
    */
    const std::string & value() const;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Parameter value
    */
    void setValue(const std::string & value);


protected:
    std::string   m_name;     ///< Parameter name (e.g., "filename")
    OptionalState m_optional; ///< Optional-state
    std::string   m_value;    ///< Parameter value
};


} // namespace cppassist
