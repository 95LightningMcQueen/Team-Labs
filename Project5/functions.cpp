#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

void CheckInputFile(std::ifstream& fin)
{
    if (!fin.good())
    {
        throw std::runtime_error("Файл не существует. \n");
    }
    if (!fin)
    {
        throw std::runtime_error("Ошибка входного файла. \n");
    }
    if (fin.peek() == EOF)
    {
        throw std::runtime_error("Файл пуст. \n");
    }
}

void CheckOutputFile(std::ofstream& fout)
{
    if (!fout.good())
    {
        throw std::runtime_error("Файл не существует. \n");
    }
    if (!fout)
    {
        throw std::runtime_error("Ошибка выходного файла. \n");
    }
}

void ConvertStudentToBinary(std::ifstream& fin, std::ofstream& fout)
{
    std::string line;
    while (std::getline(fin, line))
    {
        Student student;
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ';');
        student.number = std::stoi(token);
        std::getline(ss, token, ';');
        std::strncpy(student.surname, token.c_str(), sizeof(student.surname));
        std::getline(ss, token, ';');
        std::strncpy(student.name, token.c_str(), sizeof(student.name));
        std::getline(ss, token, ';');
        std::strncpy(student.patronymic, token.c_str(), sizeof(student.patronymic));

        fout.write(reinterpret_cast<char*>(&student), sizeof(Student));
    }
}

void ConvertMarksToBinary(std::ifstream& fin, std::ofstream& fout)
{
    std::string line;
    while (std::getline(fin, line))
    {
        StudentMarks marks;
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ';');
        marks.group = std::stoi(token);
        std::getline(ss, token, ';');
        marks.number = std::stoi(token);
        std::getline(ss, token, ';');
        std::getline(ss, token, ';');
        marks.ma = std::stoi(token);
        std::getline(ss, token, ';');
        std::getline(ss, token, ';');
        marks.geo = std::stoi(token);
        std::getline(ss, token, ';');
        std::getline(ss, token, ';');
        marks.prog = std::stoi(token);

        fout.write(reinterpret_cast<char*>(&marks), sizeof(StudentMarks));
    }
}

void MergeBinFile(std::ifstream& finA, std::ifstream& finB, std::ofstream& fout)
{
    Student student;
    StudentMarks studentMarks;

    while (finA.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        finB.clear();
        finB.seekg(0);

        while (finB.read(reinterpret_cast<char*>(&studentMarks), sizeof(StudentMarks)))
        {
            StudentInfo studentInfo;

            if (student.number == studentMarks.number)
            {
                studentInfo.number = studentMarks.number;
                studentInfo.geo = studentMarks.geo;
                studentInfo.group = studentMarks.group;
                studentInfo.ma = studentMarks.ma;
                studentInfo.prog = studentMarks.prog;

                std::strcpy(studentInfo.name, student.name);
                std::strcpy(studentInfo.patronymic, student.patronymic);
                std::strcpy(studentInfo.surname, student.surname);

                fout.write(reinterpret_cast<char*>(&studentInfo), sizeof(studentInfo));
            }
        }
    }
}

void CalculatingAverageMarks(std::ifstream& fin, std::ofstream& fout)
{
    StudentInfo studentInfo;

    while (fin.read(reinterpret_cast<char*>(&studentInfo), sizeof(StudentInfo)))
    {
        StudentAvg studentAvg;

        studentAvg.number = studentInfo.number;
        studentAvg.group = studentInfo.group;

        std::strcpy(studentAvg.name, studentInfo.name);
        std::strcpy(studentAvg.surname, studentInfo.surname);
        std::strcpy(studentAvg.patronymic, studentInfo.patronymic);

        studentAvg.avgMarks = (studentInfo.geo + studentInfo.ma + studentInfo.prog) / 3;

        fout.write(reinterpret_cast<char*>(&studentAvg), sizeof(studentAvg));
    }
}

void SearchingFailingStudent(std::ifstream& fin, std::ofstream& fout)
{
    StudentAvg studentAvg;

    while (fin.read(reinterpret_cast<char*>(&studentAvg), sizeof(StudentAvg)))
    {
        FailingStudent failingStudent;

        if (studentAvg.avgMarks < 4)
        {
            failingStudent.number = studentAvg.number;
            failingStudent.group = studentAvg.group;

            std::strcpy(failingStudent.surname, studentAvg.surname);

            fout.write(reinterpret_cast<char*>(&failingStudent), sizeof(failingStudent));
        }
    }
}

void BubbleSortStudents(FailingStudent* failingStudents, int64_t size)
{
    for (int64_t i = 0; i < size - 1; ++i)
    {
        for (int64_t j = 0; j < size - i - 1; ++j)
        {
            if (failingStudents[j].group > failingStudents[j + 1].group)
            {
                FailingStudent temp = failingStudents[j];
                failingStudents[j] = failingStudents[j + 1];
                failingStudents[j + 1] = temp;
            }
            else if (failingStudents[j].group == failingStudents[j + 1].group)
            {
                if (strcmp(failingStudents[j].surname, failingStudents[j + 1].surname) > 0)
                {
                    FailingStudent temp = failingStudents[j];
                    failingStudents[j] = failingStudents[j + 1];
                    failingStudents[j + 1] = temp;
                }
            }
        }
    }
}

void ConvertBinaryToTxt(std::ifstream& fin, std::ofstream& fout)
{
    FailingStudent failingStudent;

    while (fin.read(reinterpret_cast<char*>(&failingStudent), sizeof(FailingStudent)))
    {
        fout << failingStudent.surname << ";" << failingStudent.group << ";" << failingStudent.number << "\n";
    }
}

FailingStudent* MakeArrayFromBin(std::ifstream& fin, int64_t& size)
{
    fin.seekg(0, std::ios::end);
    int64_t binSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    size = binSize / sizeof(FailingStudent);

    FailingStudent* arr = new FailingStudent[size];

    fin.read(reinterpret_cast<char*>(arr), binSize);

    return arr;
}

void MakeTxtFromArray(std::ofstream& fout, int64_t size, FailingStudent* arr)
{
    for (int64_t i = 0; i < size; ++i)
    {
        fout << arr[i].surname << ";" << arr[i].group << ";" << arr[i].number << "\n";
    }
}

void MergeTxtFile(std::ifstream& finA, std::ifstream& finB, std::ofstream& fout)
{
    std::string line;
    while (std::getline(finA, line))
    {
        fout << line << '\n';
    }
    fout << '\n';
    while (std::getline(finB, line))
    {
        fout << line << '\n';
    }
}

void CreatingListByGroup(std::ifstream& fin, std::ofstream& fout, int32_t group)
{
    StudentInfo studentInfo;

    while (fin.read(reinterpret_cast<char*>(&studentInfo), sizeof(StudentInfo)))
    {
        if (group == studentInfo.group)
        {
            fout.write(reinterpret_cast<char*>(&studentInfo), sizeof(studentInfo));
        }
    }
}

void SortGroupByAlphabet(std::ifstream& fin, std::ofstream& fout)
{
    fin.seekg(0, std::ios::end);
    int64_t fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    int32_t size = fileSize / sizeof(StudentInfo);
    StudentInfo* arr = new StudentInfo[size];

    fin.read(reinterpret_cast<char*>(arr), fileSize);

    for (int64_t i = 0; i < size - 1; ++i)
    {
        for (int64_t j = 0; j < size - i - 1; ++j)
        {
            if (std::strcmp(arr[j].surname, arr[j + 1].surname) > 0)
            {
                StudentInfo temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    fout.write(reinterpret_cast<char*>(arr), fileSize);

    delete[] arr;
}

void CreatingListByAvg(std::ifstream& fin, std::ofstream& fout, int32_t group)
{
    StudentAvg studentAvg;

    while (fin.read(reinterpret_cast<char*>(&studentAvg), sizeof(StudentAvg)))
    {
        if (group == studentAvg.group)
        {
            fout.write(reinterpret_cast<char*>(&studentAvg), sizeof(studentAvg));
        }
    }
}

void SortGroupByAvg(std::ifstream& fin, std::ofstream& fout)
{
    fin.seekg(0, std::ios::end);
    int64_t fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    int64_t size = fileSize / sizeof(StudentAvg);
    StudentAvg* arr = new StudentAvg[size];

    fin.read(reinterpret_cast<char*>(arr), fileSize);

    for (int64_t i = 0; i < size - 1; ++i)
    {
        for (int64_t j = 0; j < size - i - 1; ++j)
        {
            if (arr[j].avgMarks < arr[j + 1].avgMarks)
            {
                StudentAvg temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    fout.write(reinterpret_cast<char*>(arr), fileSize);

    delete[] arr;
}

void SearchingExcellentStudent(std::ifstream& fin, std::ofstream& fout)
{
    StudentAvg studentAvg;

    while (fin.read(reinterpret_cast<char*>(&studentAvg), sizeof(StudentAvg)))
    {
        ExcellentStudent excellentStudent;

        if (studentAvg.avgMarks > 7)
        {
            excellentStudent.number = studentAvg.number;
            excellentStudent.group = studentAvg.group;

            std::strcpy(excellentStudent.surname, studentAvg.surname);

            fout.write(reinterpret_cast<char*>(&excellentStudent), sizeof(excellentStudent));
        }
    }
}

void SortExcellent(std::ifstream& fin, std::ofstream& fout)
{
    fin.seekg(0, std::ios::end);
    int64_t fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    int32_t size = fileSize / sizeof(ExcellentStudent);
    ExcellentStudent* arr = new ExcellentStudent[size];

    fin.read(reinterpret_cast<char*>(arr), fileSize);

    for (int32_t i = 0; i < size - 1; ++i)
    {
        for (int32_t j = 0; j < size - i - 1; ++j)
        {
            if (std::strcmp(arr[j].surname, arr[j + 1].surname) > 0)
            {
                ExcellentStudent temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    fout.write(reinterpret_cast<char*>(arr), fileSize);
    delete[] arr;
}

void MakeTxtForGroup(std::ifstream& fin, std::ofstream& fout)
{
    StudentInfo studentInfo;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while (fin.read(reinterpret_cast<char*>(&studentInfo), sizeof(StudentInfo)))
    {
        fout << studentInfo.group << ';' << studentInfo.surname << ';' << studentInfo.name << ';' << studentInfo.patronymic << ';' << studentInfo.number << ";ГЕО;" << studentInfo.geo << ";МА;" << studentInfo.ma << ";ПРОГ;" << studentInfo.prog << '\n';
    }
}

void PrintConsoleForGroup(std::ifstream& fin)
{
    StudentInfo studentInfo;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while (fin.read(reinterpret_cast<char*>(&studentInfo), sizeof(StudentInfo)))
    {
        std::cout << studentInfo.group << ';' << studentInfo.surname << ';' << studentInfo.name << ';' << studentInfo.patronymic << ';' << studentInfo.number << ";ГЕО;" << studentInfo.geo << ";МА;" << studentInfo.ma << ";ПРОГ;" << studentInfo.prog << '\n';
    }
}

void MakeTxtForAvg(std::ifstream& fin, std::ofstream& fout)
{
    StudentAvg studentAvg;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while (fin.read(reinterpret_cast<char*>(&studentAvg), sizeof(StudentAvg)))
    {
        fout << studentAvg.group << ';' << studentAvg.surname << ';' << studentAvg.name << ';' << studentAvg.patronymic << ';' << studentAvg.number << ';' << studentAvg.avgMarks << '\n';
    }
}

void PrintConsoleForAvg(std::ifstream& fin)
{
    StudentAvg studentAvg;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while (fin.read(reinterpret_cast<char*>(&studentAvg), sizeof(StudentAvg)))
    {
        std::cout << studentAvg.group << ';' << studentAvg.surname << ';' << studentAvg.name << ';' << studentAvg.patronymic << ';' << studentAvg.number << ';' << studentAvg.avgMarks << '\n';
    }
}

void MakeTxtForExcellent(std::ifstream& fin, std::ofstream& fout)
{
    ExcellentStudent excellentStudent;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while (fin.read(reinterpret_cast<char*>(&excellentStudent), sizeof(ExcellentStudent)))
    {
        fout << excellentStudent.group << ';' << excellentStudent.surname << ';' << excellentStudent.number << '\n';
    }
}

void PrintConsoleForExcellent(std::ifstream& fin)
{
    ExcellentStudent excellentStudent;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while (fin.read(reinterpret_cast<char*>(&excellentStudent), sizeof(ExcellentStudent)))
    {
        std::cout << excellentStudent.group << ';' << excellentStudent.surname << ';' << excellentStudent.number << '\n';
    }
}

int32_t InputGroup()
{
    int32_t group{};
    std::cout << "Введите номер группы: ";
    std::cin >> group;
    return group;
}