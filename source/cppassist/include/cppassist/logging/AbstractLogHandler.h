
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


class LogMessage;


/**
*  @brief
*    Abstract log message handler
*
*    cppassist uses a global logging handler to which all generated log
*    messages are dispatched. This is the abstract interface for handling them.
*    Subclass this class if you wish to replace the global default logging
*    behavior in cppassist, which is to write everything to stdout.
*
*  @see setLoggingHandler
*  @see logging.h
*/
class CPPASSIST_API AbstractLogHandler
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractLogHandler();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractLogHandler();

    /**
    *  @brief
    *    Handle log message
    *
    *  @param[in] message
    *    Log message
    */
    virtual void handle(const LogMessage & message) = 0;


protected:
    /**
    *  @brief
    *    Construct prefix from message context
    *
    *  @param[in] message
    *    Log message
    *
    *  @return
    *    Prefix
    */
    static std::string messagePrefix(const LogMessage & message);

    /**
    *  @brief
    *    Construct string denoting log level
    *
    *  @param[in] level
    *    Log level
    *
    *  @return
    *    String denoting log level
    */
    static std::string levelString(int level);
};


} // namespace cppassist
