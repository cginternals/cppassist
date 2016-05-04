
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
*  @remarks
*    All log messages above the current verbosity level are omitted.
*/
CPPASSIST_API LogMessage::Level verbosityLevel();

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
CPPASSIST_API void setVerbosityLevel(LogMessage::Level verbosity);

/**
*  @brief
*    Get log stream
*
*    Use the stream interface to create log messages.
*    Example:
*      \code{.cpp}
*      log(LogMessage::Info) << "Message: " << 3.14;
*      \endcode
*
*  @param[in] context
*    User defined context string
*  @param[in] level
*    Log level
*
*  @return
*    Log stream interface
*/
CPPASSIST_API LogMessageBuilder log(const std::string & context = "", LogMessage::Level level = LogMessage::Info);

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
*    Get log stream for fatal errors
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
CPPASSIST_API LogMessageBuilder fatal(const std::string & context = "");

/**
*  @brief
*    Write a formatted string to the info log
*
*    Example:
*    \code{.cpp}
*        fInfo("This is a test: %; pi = %+0E10.5;", 42, 3.141592653589793); // output: "This is a test: 42 pi = +3.14159E+00"
*        fInfo("%; - %X; - %rf?_10.2;", "a string", 255, 2.71828182846); // output: "a string - 255 - ______2.72"
*    \endcode
*
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] arguments
*    Arguments according to the format string
*
*  @see
*    formatString
*/
template <typename... Arguments>
void fInfo(const char * format, Arguments... arguments);

/**
*  @brief
*    Write a formatted string to the debug log
*
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] arguments
*    Arguments according to the format string
*
*  @see
*    fInfo
*/
template <typename... Arguments>
void fDebug(const char * format, Arguments... arguments);

/**
*  @brief
*    Write a formatted string to the warning log
*
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] arguments
*    Arguments according to the format string
*
*  @see
*    fInfo
*/
template <typename... Arguments>
void fWarning(const char * format, Arguments... arguments);

/**
*  @brief
*    Write a formatted string to the critical error log
*
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] arguments
*    Arguments according to the format string
*
*  @see
*    fInfo
*/
template <typename... Arguments>
void fCritical(const char * format, Arguments... arguments);

/**
*  @brief
*    Write a formatted string to the fatal error log
*
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] arguments
*    Arguments according to the format string
*
*  @see
*    fInfo
*/
template <typename... Arguments>
void fFatal(const char * format, Arguments... arguments);


} // namespace cppassist


#include <cppassist/logging/logging.hpp>
