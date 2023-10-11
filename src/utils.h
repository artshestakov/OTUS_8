#pragma once
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <chrono>
//-----------------------------------------------------------------------------
namespace utils
{
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    //! ѕолучить список путей к файлам в директории
    //! \param dir_path путь к директории
    //! \param is_recursive указывает, использовать ли рекурсивный обход директории
    //! \return возвращает список путей к файлам
    std::vector<std::string> DirFiles(const std::string& dir_path, bool is_recursive = false);

    //! ¬ычислить хэш строки
    //! \param s строка
    //! \return возвращает хэш строки
    std::string MD5(const std::string& s);

    //! ѕолучить текущий момент времени
    //! \return возвращает текущий момент времени
    TimePoint GetTick();

    //! ѕолучить разницу между указанным моментом времени и текущим
    //! \param p момент времени
    //! \return возвращает разницу между указанным моментом времени и текущим
    uint64_t GetTickDiff(const TimePoint& p);
}
//-----------------------------------------------------------------------------
