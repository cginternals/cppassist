
#pragma once


#include <cppassist/logging/LogMessage.h>
#include <cppassist/logging/LogMessageBuilder.h>


namespace cppassist
{


class AbstractLogHandler;
class LogMessageBuilder;


/**
*  @brief
*    Get global logging handler
*
*  @return
*    Logging handler (can be null)
*/
CPPASSIST_API AbstractLogHandler * loggingHandler();

/**
*  @brief
*    Set global logging handler
*
*  @param[in] handler
*    Logging handler (can be null)
*/
CPPASSIST_API void setLoggingHandler(AbstractLogHandler * handler);

/**
*  @brief
*    Get current log level
*
*  @return
*    Log level
*
*  @remark
*    All log messages above the current verbosity level are omitted.
*/
CPPASSIST_API int verbosityLevel();

/**
*  @brief
*    Set current log level
*
*  @param[in] verbosity
*    Log level
*
*  @see
*    verbosityLevel
*/
CPPASSIST_API void setVerbosityLevel(int verbosity);

/**
*  @brief
*    Get log stream
*
*    Use the stream interface to create log messages.
*    Example:
*    @code{.cpp}
*      log(LogMessage::Info) << "Message: " << 3.14;
*    @endcode
*
*  @param[in] level
*    Log level
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*/
CPPASSIST_API LogMessageBuilder log(int level, const std::string & context = "");

/**
*  @brief
*    Get log stream for critical errors
*
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*
*  @see
*    log
*/
CPPASSIST_API LogMessageBuilder critical(const std::string & context = "");

/**
*  @brief
*    Get log stream for error messages
*
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*
*  @see
*    log
*/
CPPASSIST_API LogMessageBuilder error(const std::string & context = "");

/**
*  @brief
*    Get log stream for warning messages
*
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*
*  @see
*    log
*/
CPPASSIST_API LogMessageBuilder warning(const std::string & context = "");

/**
*  @brief
*    Get log stream for info messages
*
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*
*  @see
*    log
*/
CPPASSIST_API LogMessageBuilder info(const std::string & context = "");

/**
*  @brief
*    Get log stream for debug messages
*
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*
*  @see
*    log
*/
CPPASSIST_API LogMessageBuilder debug(const std::string & context = "");

/**
*  @brief
*    Get log stream for debug messages at a given debug level
*
*  @param[in] debugLevel
*    Debug level (e.g., 0 for debug, 1 for debug+1, etc.)
*  @param[in] context
*    User defined context string
*
*  @return
*    Log stream interface
*
*  @see
*    log
*/
CPPASSIST_API LogMessageBuilder debug(unsigned int debugLevel, const std::string & context = "");


} // namespace cppassist
