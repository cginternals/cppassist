
#include <cppassist/logging/LogMessage.h>


namespace cppassist
{


LogMessage::LogMessage(int level, const std::string & message, const std::string & context)
: m_level(level)
, m_message(message)
, m_context(context)
{
}

int LogMessage::level() const
{
    return m_level;
}

const std::string & LogMessage::message() const
{
    return m_message;
}

const std::string & LogMessage::context() const
{
    return m_context;
}


} // namespace cppassist
