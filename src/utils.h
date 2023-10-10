#pragma once
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
//-----------------------------------------------------------------------------
namespace utils
{
    std::vector<std::string> DirFiles(const std::string& dir_path);
    std::string MD5(const std::string& s);
}
//-----------------------------------------------------------------------------
