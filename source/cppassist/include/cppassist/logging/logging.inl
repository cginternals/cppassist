
#pragma once


#include <cassert>

#include <cppassist/logging/formatString.h>


namespace cppassist
{


template <typename... Arguments>
void fCritical(const char * format, Arguments... arguments)
{
    assert(format != nullptr);

    critical() << formatString(format, arguments...);
}

template <typename... Arguments>
void fError(const char * format, Arguments... arguments)
{
    assert(format != nullptr);

    error() << formatString(format, arguments...);
}

template <typename... Arguments>
void fWarning(const char * format, Arguments... arguments)
{
    assert(format != nullptr);

    warning() << formatString(format, arguments...);
}

template <typename... Arguments>
void fInfo(const char * format, Arguments... arguments)
{
    assert(format != nullptr);

    info() << formatString(format, arguments...);
}

template <typename... Arguments>
void fDebug(const char * format, Arguments... arguments)
{
    assert(format != nullptr);

    debug() << formatString(format, arguments...);
}

template <typename... Arguments>
void fDebug(unsigned int debugLevel, const char * format, Arguments... arguments)
{
    assert(format != nullptr);

    debug(debugLevel) << formatString(format, arguments...);
}


} // namespace cppassist
