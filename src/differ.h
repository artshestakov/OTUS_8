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

    //! Получить текстовое описание последней ошибки
    //! \return возвращает текстовое описание последней ошибки
    const std::string& GetErrorString() const;

    //! Инициализация класса
    //! \return возвращает true в случае успеха, иначе - false
    bool Init();

    //! Запуск поиска дубликатов
    //! \return возвращает true в случае успеха, иначе - false
    bool Run();

private:

    //! Сравнение файлов
    //! \param file_path_left первый файл
    //! \param file_path_right правый файл
    //! \return возвращает true в случае если файлы одинаковые, иначе - false
    bool Diff(std::ifstream& file, const std::string& file_path_right, uint64_t size);

    //! Добавить похожие файлы в словарь
    //! \param file_left путь к файлу 1
    //! \param file_right путь к файлу, который идентичен с файлом 1
    void InsertToMap(const std::string& file_left, const std::string& file_right);

    //! Вывод результатов на консоль
    void PrintResult();

private:
    std::string m_ErrorString;
    std::string m_DirPath;
    std::map<std::string, std::vector<std::string>> m_MapSimilar;
};
//-----------------------------------------------------------------------------
