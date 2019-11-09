
namespace cppassist
{


template<typename E>
Error::Error(const std::string & message, const E & reason)
: m_message(message)
, m_reason(new E(reason))
{
}

template<typename E>
Error::Error(std::string && message, const E & reason)
: m_message(std::move(message))
, m_reason(new E(reason))
{
}

template<typename E>
Error::Error(const std::string & message, E && reason)
: m_message(message)
, m_reason(new E(std::move(reason)))
{
}

template<typename E>
Error::Error(std::string && message, E && reason)
: m_message(std::move(message))
, m_reason(new E(std::move(reason)))
{
}


} // namespace cppassist
