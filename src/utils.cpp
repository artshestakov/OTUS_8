#include "utils.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
//-----------------------------------------------------------------------------
std::vector<std::string> utils::DirFiles(const std::string& dir_path)
{
    std::vector<std::string> v;
    for (const auto& f : boost::make_iterator_range(boost::filesystem::directory_iterator(dir_path), { }))
    {
        v.emplace_back(f.path().string());
    }
    return v;
}
//-----------------------------------------------------------------------------
std::string utils::MD5(const std::string& s)
{
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;

    hash.process_bytes(s.data(), s.size());
    hash.get_digest(digest);

    const auto charDigest = reinterpret_cast<const char*>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), std::back_inserter(result));
    return result;
}
//-----------------------------------------------------------------------------
