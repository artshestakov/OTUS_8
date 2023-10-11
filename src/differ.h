#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
//-----------------------------------------------------------------------------
class Differ
{
public:
    Differ(const std::vector<std::string>& dir_path_list, bool is_recursive, unsigned int minimum_size);
    ~Differ();

    //! �������� ��������� �������� ��������� ������
    //! \return ���������� ��������� �������� ��������� ������
    const std::string& GetErrorString() const;

    //! ������������� ������
    //! \return ���������� true � ������ ������, ����� - false
    bool Init();

    //! ������ ������ ����������
    //! \return ���������� true � ������ ������, ����� - false
    bool Run();

private:

    //! ��������� ������
    //! \param file_path_left ������ ����
    //! \param file_path_right ������ ����
    //! \return ���������� true � ������ ���� ����� ����������, ����� - false
    bool Diff(std::ifstream& file, const std::string& file_path_right, uint64_t size);

    //! �������� ������� ����� � �������
    //! \param file_left ���� � ����� 1
    //! \param file_right ���� � �����, ������� ��������� � ������ 1
    void InsertToMap(const std::string& file_left, const std::string& file_right);

    //! ����� ����������� �� �������
    void PrintResult();

private:
    std::string m_ErrorString;
    std::vector<std::string> m_DirPathList;
    bool m_IsRecursive;
    unsigned int m_MinimumSize;
    std::map<std::string, std::vector<std::string>> m_MapSimilar;
};
//-----------------------------------------------------------------------------
