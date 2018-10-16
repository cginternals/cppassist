
#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iomanip>

#include <cppassist/logging/LogMessage.h>


namespace cppassist
{


class AbstractLogHandler;


/**
*  @brief
*    Stream interface to build LogMessage's from different kinds of primitive types
*
*    The LogMessageBuilder is usually created by one of the global functions
*    log, debug, warning, error or fatal. It works similar to streams and
*    accepts a number of different types which will be converted to strings
*    automatically. When it goes out of scope, it creates a LogMessage from
*    all streamed objects and sends it to the log handler.
*
*    Typical usage of the LogMessageBuilder:
*    @code{.cpp}
*      warning() << "This is warning number " << 3;
*    @endcode
*
*  @see logging.h
*  @see LogMessage
*  @see setLoggingHandler
*  @see setVerbosityLevel
*  @see log
*/
class CPPASSIST_API LogMessageBuilder
{
public:
    // These types are unspecified by the C++ standard -> we need to query the compiler specific types
    using PrecisionManipulator = decltype(std::setprecision(0));
    using FillManipulator      = decltype(std::setfill('0'));
    using WidthManipulator     = decltype(std::setw(0));


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] level
    *    Log level
    *  @param[in] handler
    *    Log handler (must NOT be null!)
    *  @param[in] context
    *    User defined context string
    */
    LogMessageBuilder(int level, AbstractLogHandler * handler, const std::string & context);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] builder
    *    Source object
    */
    LogMessageBuilder(const LogMessageBuilder & builder);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~LogMessageBuilder();

    // Stream operators
    LogMessageBuilder & operator<<(const char * c);
    LogMessageBuilder & operator<<(const std::string & str);
    LogMessageBuilder & operator<<(bool b);
    LogMessageBuilder & operator<<(char c);
    LogMessageBuilder & operator<<(int i);
    LogMessageBuilder & operator<<(float f);
    LogMessageBuilder & operator<<(double d);
    LogMessageBuilder & operator<<(long double d);
    LogMessageBuilder & operator<<(unsigned u);
    LogMessageBuilder & operator<<(long l);
    LogMessageBuilder & operator<<(long long l);
    LogMessageBuilder & operator<<(unsigned long ul);
    LogMessageBuilder & operator<<(unsigned long long ull);
    LogMessageBuilder & operator<<(unsigned char uc);
    LogMessageBuilder & operator<<(const void * pointer);

    template <typename T>
    LogMessageBuilder & operator<<(const T * pointer);

    template <typename T>
    LogMessageBuilder & operator<<(const std::vector<T> & vector);

    template <typename T, std::size_t Count>
    LogMessageBuilder & operator<<(const std::array<T, Count> & array);

    // Stream manipulators
    LogMessageBuilder & operator<<(std::ostream & (*manipulator)(std::ostream&));
    LogMessageBuilder & operator<<(std::ios_base & (*manipulator)(std::ios_base&));
    LogMessageBuilder & operator<<(PrecisionManipulator manipulator);
    LogMessageBuilder & operator<<(FillManipulator manipulator);

#ifndef _MSC_VER
    // On Windows: PrecisionManipulator = WidthManipulator
    LogMessageBuilder & operator<<(WidthManipulator manipulator);
#endif


protected:
    int                                m_level;   ///< Current log level
    AbstractLogHandler               * m_handler; ///< Log handler (must NOT be null!)
    std::string                        m_context; ///< User define context string
    std::shared_ptr<std::stringstream> m_stream;  ///< Used string stream
};


} // namespace cppassist


#include <cppassist/logging/LogMessageBuilder.inl>
