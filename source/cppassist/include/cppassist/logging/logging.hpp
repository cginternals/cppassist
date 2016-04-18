#pragma once


#include <cassert>

#include <cppassist/logging/formatString.h>


namespace loggingzeug
{

template <typename... Arguments> void fInfo(const char* format, Arguments... arguments)
{
    assert(format != nullptr);

    info() << formatString(format, arguments...);
}

template <typename... Arguments> void fDebug(const char* format, Arguments... arguments)
{
    assert(format != nullptr);

    debug() << formatString(format, arguments...);
}

template <typename... Arguments> void fWarning(const char* format, Arguments... arguments)
{
    assert(format != nullptr);

    warning() << formatString(format, arguments...);
}

template <typename... Arguments> void fCritical(const char* format, Arguments... arguments)
{
    assert(format != nullptr);

    critical() << formatString(format, arguments...);
}

template <typename... Arguments> void fFatal(const char* format, Arguments... arguments)
{
    assert(format != nullptr);

    fatal() << formatString(format, arguments...);
}

} // namespace loggingzeug
