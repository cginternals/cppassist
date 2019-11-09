
#include <cppassist/error/Error.h>

#include <iostream>


namespace cppassist
{


Error::Error(const std::string & message)
: m_message(message)
{
}

Error::Error(std::string && message)
: m_message(std::move(message))
{
}

Error::Error(const Error & error)
: m_message(error.m_message)
, m_reason(error.hasReason() ? error.m_reason->clone() : nullptr)
{
}

Error::Error(Error && error)
: m_message(std::move(error.m_message))
, m_reason(std::move(error.m_reason))
{
    // Reset moved error
    error.m_message = "";
    error.m_reason.reset(nullptr);
}

Error::~Error()
{
}

Error & Error::operator =(const Error & error)
{
    // Copy error
    m_message = error.m_message;
    m_reason.reset(
        error.hasReason() ? error.m_reason->clone() : nullptr
    );

    // Return error
    return *this;
}

Error & Error::operator =(Error && error)
{
    // Move error
    m_message = std::move(error.m_message);
    m_reason = std::move(error.m_reason);

    // Reset moved error
    error.m_message = "";
    error.m_reason.reset(nullptr);

    // Return error
    return *this;
}

Error * Error::clone() const
{
    // Create clone
    return new Error(*this);
}

const std::string & Error::message() const
{
    // Return error message
    return m_message;
}

bool Error::hasReason() const
{
    // Check if error has a reason
    return m_reason.get() != nullptr;
}

Error * Error::reason() const
{
    // Return reason for this error
    return m_reason.get();
}

void Error::print(const std::string & indent, const std::string & indentStep) const
{
    // Print to std::cout
    printTo(std::cout, indent, indentStep);
}

void Error::printTo(std::ostream & os, const std::string & indent, const std::string & indentStep) const
{
    // Print error message
    os << indent << message() << std::endl;

    // Print reason with increased indentation
    if (hasReason()) {
        reason()->printTo(os, indent + indentStep, indentStep);
    }
}


} // namespace cppassist
