#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
//-----------------------------------------------------------------------------
class Differ
{
public:
    Differ(const std::string& dir_path);
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
    std::string m_DirPath;
    std::map<std::string, std::vector<std::string>> m_MapSimilar;
};
//-----------------------------------------------------------------------------
