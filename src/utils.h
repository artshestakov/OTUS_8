#pragma once
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <chrono>
//-----------------------------------------------------------------------------
namespace utils
{
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    //! �������� ������ ����� � ������ � ����������
    //! \param dir_path ���� � ����������
    //! \param is_recursive ���������, ������������ �� ����������� ����� ����������
    //! \return ���������� ������ ����� � ������
    std::vector<std::string> DirFiles(const std::string& dir_path, bool is_recursive = false);

    //! ��������� ��� ������
    //! \param s ������
    //! \return ���������� ��� ������
    std::string MD5(const std::string& s);

    //! �������� ������� ������ �������
    //! \return ���������� ������� ������ �������
    TimePoint GetTick();

    //! �������� ������� ����� ��������� �������� ������� � �������
    //! \param p ������ �������
    //! \return ���������� ������� ����� ��������� �������� ������� � �������
    uint64_t GetTickDiff(const TimePoint& p);
}
//-----------------------------------------------------------------------------
