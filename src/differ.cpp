#include "differ.h"
#include "utils.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
//-----------------------------------------------------------------------------
constexpr int BUFFER_CHUNK = 5;
//-----------------------------------------------------------------------------
Differ::Differ(const std::string& dir_path)
    : m_DirPath(dir_path)
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
    if (m_DirPath.empty())
    {
        m_ErrorString = "The path is empty";
        return false;
    }

    //Проверим, что указанный путь это путь к директории
    if (!boost::filesystem::is_directory(m_DirPath))
    {
        m_ErrorString = "The path \"" + m_DirPath + "\" is not a directory";
        return false;
    }

    return true;
}
//-----------------------------------------------------------------------------
bool Differ::Run()
{
    std::vector<std::string> files = utils::DirFiles(m_DirPath);
    if (files.size() < 2)
    {
        m_ErrorString = "The directory \"" + m_DirPath + "\" has less than two files";
        return false;
    }

    for (auto file_left = files.begin(); file_left != files.end(); ++file_left)
    {
        //Не обращаем внимания на файлы меньше одного байта
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
            //Игнорируем файлы с разным размером. Очевидно что они разные по содержанию.
            //А так же, игнорируем одинаковость текущий файл с очередным
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
        //Вычисляем, сколько будем читать: указанный буфер или то, что осталось
        cnt = size < BUFFER_CHUNK ? size : BUFFER_CHUNK;

        file.read(c1, cnt);
        file_right.read(c2, cnt);
        size -= cnt;

        //Если хэши разные - выходим
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
    //Убедимся, что такого файла ещё нет
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
