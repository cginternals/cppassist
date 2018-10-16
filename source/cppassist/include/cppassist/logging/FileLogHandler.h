
#pragma once


#include <cppassist/logging/AbstractLogHandler.h>
#include <cppassist/logging/LogMessage.h>


namespace cppassist
{


/**
*  @brief
*    Log message handler that writes log messages a file
*
*  @see setLoggingHandler
*  @see logging.h
*/
class CPPASSIST_API FileLogHandler : public AbstractLogHandler
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] logfile
    *    File name
    */
    FileLogHandler(const std::string & logfile = "logfile.log");

    // Virtual AbstractLogHandler interface
    virtual void handle(const LogMessage & message) override;


protected:
    std::string m_logfile; ///< File name of the log file
};


} // namespace cppassist
