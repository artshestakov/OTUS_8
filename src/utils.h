#pragma once
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <chrono>
//-----------------------------------------------------------------------------
namespace utils
{
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    //! Получить список путей к файлам в директории
    //! \param dir_path путь к директории
    //! \param is_recursive указывает, использовать ли рекурсивный обход директории
    //! \return возвращает список путей к файлам
    std::vector<std::string> DirFiles(const std::string& dir_path, bool is_recursive = false);

    //! Вычислить хэш строки
    //! \param s строка
    //! \return возвращает хэш строки
    std::string MD5(const std::string& s);

    TimePoint GetTick();
    uint64_t GetTickDiff(const TimePoint& p);
}
//-----------------------------------------------------------------------------
