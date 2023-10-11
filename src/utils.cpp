#include "utils.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
//-----------------------------------------------------------------------------
std::vector<std::string> utils::DirFiles(const std::string& dir_path, const std::vector<std::string>& exclude_dir_list, bool is_recursive)
{
    std::vector<std::string> v;
    auto read_directory = [&v, &exclude_dir_list](auto iterator_type)
    {
        for (const auto& f : boost::make_iterator_range(iterator_type, { }))
        {
            auto f_path = f.path();
            if (!is_directory(f) && !VectorContains(exclude_dir_list, f_path.parent_path().string()))
            {
                v.emplace_back(f_path.string());
            }
        }
    };

    is_recursive ?
        read_directory(boost::filesystem::recursive_directory_iterator(dir_path)) :
        read_directory(boost::filesystem::directory_iterator(dir_path));
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
utils::TimePoint utils::GetTick()
{
    return std::chrono::steady_clock::now();
}
//-----------------------------------------------------------------------------
uint64_t utils::GetTickDiff(const utils::TimePoint& p)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(utils::GetTick() - p).count();
}
//-----------------------------------------------------------------------------
