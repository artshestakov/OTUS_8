#include "differ.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
//-----------------------------------------------------------------------------
constexpr int BUFFER_CHUNK = 5;
//-----------------------------------------------------------------------------
Differ::Differ(const std::vector<std::string>& dir_path_list, bool is_recursive)
    : m_DirPathList(dir_path_list),
    m_IsRecursive(is_recursive)
{

}
//-----------------------------------------------------------------------------
Differ::~Differ()
{

}
//-----------------------------------------------------------------------------
const std::string& Differ::GetErrorString() const
{
    return m_ErrorString;
}
//-----------------------------------------------------------------------------
bool Differ::Init()
{
    if (m_DirPathList.empty())
    {
        m_ErrorString = "The list of path is empty";
        return false;
    }

    //��������, ��� ��������� ���� ��� ���� � ����������
    for (const std::string& dir_path : m_DirPathList)
    {
        if (!boost::filesystem::is_directory(dir_path))
        {
            m_ErrorString = "The path \"" + dir_path + "\" is not a directory";
            return false;
        }
    }

    return true;
}
//-----------------------------------------------------------------------------
bool Differ::Run()
{
    auto t = utils::GetTick();
    std::vector<std::string> files;
    for (const std::string& dir_path : m_DirPathList)
    {
        auto f = utils::DirFiles(dir_path, m_IsRecursive);
        files.insert(files.end(), f.begin(), f.end());
    }

    if (auto s = files.size(); s < 2)
    {
        m_ErrorString = "In total your directories has less than two files (" + std::to_string(s);
        return false;
    }
    uint64_t read_dir_ms = utils::GetTickDiff(t);

    t = utils::GetTick();

    for (auto file_left = files.begin(); file_left != files.end(); ++file_left)
    {
        //�� �������� �������� �� ����� ������ ������ �����
        uint64_t file_left_size = boost::filesystem::file_size(*file_left);
        if (file_left_size < 1)
        {
            continue;
        }

        std::ifstream file(*file_left);
        if (!file.is_open())
        {
            throw std::runtime_error("Can't open file " + *file_left);
        }

        for (auto file_other = files.begin(); file_other != files.end(); ++file_other)
        {
            //���������� ����� � ������ ��������. �������� ��� ��� ������ �� ����������.
            //� ��� ��, ���������� ������������ ������� ���� � ���������
            if (boost::filesystem::file_size(*file_other) != file_left_size ||
                file_left == file_other)
            {
                continue;
            }

            if (Diff(file, *file_other, file_left_size))
            {
                InsertToMap(*file_left, *file_other);
            }
        }
    }

    uint64_t process_ms = utils::GetTickDiff(t);

    PrintResult();

    std::cout << "Read the directory time: " << read_dir_ms << " msec" << std::endl;
    std::cout << "Diff process time:       " << process_ms << " msec" << std::endl;

    return true;
}
//-----------------------------------------------------------------------------
bool Differ::Diff(std::ifstream& file, const std::string& file_path_right, uint64_t size)
{
    std::ifstream file_right(file_path_right);
    if (!file_right.is_open())
    {
        throw std::runtime_error("Can't open file " + file_path_right);
    }

    static char c1[BUFFER_CHUNK + 1] = { 0 };
    static char c2[BUFFER_CHUNK + 1] = { 0 };
    uint64_t cnt = 0;
    bool result = false;

    while (size > 0)
    {
        //���������, ������� ����� ������: ��������� ����� ��� ��, ��� ��������
        cnt = size < BUFFER_CHUNK ? size : BUFFER_CHUNK;

        file.read(c1, cnt);
        file_right.read(c2, cnt);
        size -= cnt;

        //���� ���� ������ - �������
        result = utils::MD5(c1) == utils::MD5(c2);
        if (!result)
        {
            break;
        }
    }

    memset(c1, 0, BUFFER_CHUNK + 1);
    memset(c2, 0, BUFFER_CHUNK + 1);
    return result;
}
//-----------------------------------------------------------------------------
void Differ::InsertToMap(const std::string& file_left, const std::string& file_right)
{
    //��������, ��� ������ ����� ��� ���
    bool already_exists = false;
    for (const auto& map_item : m_MapSimilar)
    {
        already_exists = std::find(map_item.second.begin(), map_item.second.end(), file_left) != map_item.second.end();
        if (already_exists)
        {
            break;
        }
    }

    if (!already_exists)
    {
        m_MapSimilar[file_left].emplace_back(file_right);
    }
}
//-----------------------------------------------------------------------------
void Differ::PrintResult()
{
    for (const auto& map_item : m_MapSimilar)
    {
        std::cout << map_item.first << std::endl;
        for (const std::string& file_path : map_item.second)
        {
            std::cout << "  " << file_path << std::endl;
        }
        std::cout << std::endl;
    }
}
//-----------------------------------------------------------------------------
