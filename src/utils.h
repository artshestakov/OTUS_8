#pragma once
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
//-----------------------------------------------------------------------------
namespace utils
{
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    //! �������� ������ ����� � ������ � ����������
    //! \param dir_path ���� � ����������
    //! \param is_recursive ���������, ������������ �� ����������� ����� ����������
    //! \return ���������� ������ ����� � ������
    std::vector<std::string> DirFiles(const std::string& dir_path, const std::vector<std::string>& exclude_dir_list,
        const std::vector<std::string>& mask_list, bool is_recursive = false);

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

    //! ���������� ������ � ������� ��������
    //! \param s ������
    void StringToLower(std::string& s);

    //! ��������� ������� �������� � �������
    //! \param v ������
    //! \param val ��������
    //! \return ���������� true ����� ������� ������������, ����� - false
    template <typename T>
    bool VectorContains(const std::vector<T>& v, T val)
    {
        return std::find(v.begin(), v.end(), val) != v.end();
    }
}
//-----------------------------------------------------------------------------
