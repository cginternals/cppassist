
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{
namespace fs
{


/**
*  @brief
*    Create directory
*
*  @param[in] path
*    Path to directory
*
*  @return
*    0 on success, error code > 0 otherwise
*/
CPPASSIST_API int makeDir(const std::string & path);


} // nameapace fs
} // namespace cppassist
