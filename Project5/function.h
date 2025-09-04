#pragma once
#include <iostream>
#include <fstream>


struct Student
{
    int32_t number;
    char surname[100];
    char name[100];
    char patronymic[100];
};

struct StudentMarks
{
    int32_t group;
    int32_t number;
    int32_t ma;
    int32_t geo;
    int32_t prog;
};

struct StudentInfo
{
    int32_t number;
    char surname[100];
    char name[100];
    char patronymic[100];
    int32_t group;
    int32_t ma;
    int32_t geo;
    int32_t prog;
};

struct StudentAvg
{
    int32_t number;
    char surname[100];
    char name[100];
    char patronymic[100];
    int32_t group;
    int32_t avgMarks;
};

struct FailingStudent
{
    char surname[100];
    int32_t group;
    int32_t number;
};

struct ExcellentStudent
{
    char surname[100];
    int32_t group;
    int32_t number;
};


void CheckInputFile(std::ifstream&);//1
void CheckOutputFile(std::ofstream&);
void ConvertMarksToBinary(std::ifstream&, std::ofstream&);//2
void ConvertStudentToBinary(std::ifstream&, std::ofstream&);
void MergeBinFile(std::ifstream&, std::ifstream&, std::ofstream&);//3
void CalculatingAverageMarks(std::ifstream&, std::ofstream&); //4
void SearchingFailingStudent(std::ifstream&, std::ofstream&);//5
void ConvertBinaryToTxt(std::ifstream&, std::ofstream&);//6
FailingStudent* MakeArrayFromBin(std::ifstream&, int64_t&);
void BubbleSortStudents(FailingStudent*, int64_t);//7
void MakeTxtFromArray(std::ofstream&, int64_t, FailingStudent*);//8
void MergeTxtFile(std::ifstream&, std::ifstream&, std::ofstream&);
void CreatingListByGroup(std::ifstream&, std::ofstream&, int32_t);//9
void SortGroupByAlphabet(std::ifstream&, std::ofstream&);
void CreatingListByAvg(std::ifstream&, std::ofstream&, int32_t);//10
void SortGroupByAvg(std::ifstream&, std::ofstream&);
void SearchingExcellentStudent(std::ifstream&, std::ofstream&);//11
void SortExcellent(std::ifstream&, std::ofstream&);
void MakeTxtForGroup(std::ifstream&, std::ofstream&);//12
void PrintConsoleForGroup(std::ifstream&);
void PrintConsoleForAvg(std::ifstream&);//13
void MakeTxtForAvg(std::ifstream&, std::ofstream&);
void MakeTxtForExcellent(std::ifstream&, std::ofstream&);//14
void PrintConsoleForExcellent(std::ifstream&);
int32_t InputGroup();