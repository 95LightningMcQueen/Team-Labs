#include "function.h"

int main()
{
    try
    {
        setlocale(LC_ALL, "Ru");
        std::ifstream finA("in1.txt");
        CheckInputFile(finA);
        std::ofstream foutA("in1.bin", std::ios::binary);
        CheckOutputFile(foutA);
        ConvertStudentToBinary(finA, foutA);
        finA.close();
        foutA.close();

        std::ifstream finB("in2.txt");
        CheckInputFile(finB);
        std::ofstream foutB("in2.bin", std::ios::binary);
        CheckOutputFile(foutB);
        ConvertMarksToBinary(finB, foutB);
        finB.close();
        foutB.close();

        std::ifstream finC("in1.bin", std::ios::binary);
        CheckInputFile(finC);
        std::ifstream finD("in2.bin", std::ios::binary);
        CheckInputFile(finD);
        std::ofstream fout("studentinfo.bin", std::ios::binary);
        CheckOutputFile(fout);
        MergeBinFile(finC, finD, fout);
        finC.close();
        finD.close();
        fout.close();

        std::ifstream finInfo("studentinfo.bin", std::ios::binary);
        CheckInputFile(finInfo);
        std::ofstream foutAVG("studentavg.bin", std::ios::binary);
        CheckOutputFile(foutAVG);
        CalculatingAverageMarks(finInfo, foutAVG);
        finInfo.close();
        foutAVG.close();

        std::ifstream finAVG("studentavg.bin", std::ios::binary);
        CheckInputFile(finAVG);
        std::ofstream foutFalling("fallingstudent.bin", std::ios::binary);
        CheckOutputFile(foutFalling);
        SearchingFailingStudent(finAVG, foutFalling);
        finAVG.close();
        foutFalling.close();

        std::ifstream finFallingB("fallingstudent.bin", std::ios::binary);
        CheckInputFile(finFallingB);
        std::ofstream foutNoSort("fallingstudentnosort.txt");
        CheckOutputFile(foutNoSort);
        ConvertBinaryToTxt(finFallingB, foutNoSort);
        finFallingB.close();
        foutNoSort.close();

        std::ifstream finFallingSorted("fallingstudent.bin", std::ios::binary);
        CheckInputFile(finFallingSorted);
        int64_t size{};
        FailingStudent* arr = MakeArrayFromBin(finFallingSorted, size);
        finFallingSorted.close();

        BubbleSortStudents(arr, size);

        std::ofstream foutSort("fallingstudentsort.txt");
        CheckOutputFile(foutSort);
        MakeTxtFromArray(foutSort, size, arr);
        foutSort.close();
        delete[] arr;

        std::ifstream finNoSort("fallingstudentnosort.txt");
        CheckInputFile(finNoSort);
        std::ifstream finSort("fallingstudentsort.txt");
        CheckInputFile(finSort);
        std::ofstream foutMerged("fallingstudentmerged.txt");
        CheckOutputFile(foutMerged);

        MergeTxtFile(finNoSort, finSort, foutMerged);

        finNoSort.close();
        finSort.close();
        foutMerged.close();

        int32_t group = InputGroup();

        std::ifstream finGroup("studentinfo.bin", std::ios::binary);
        CheckInputFile(finGroup);
        std::ofstream foutGroup("studentgroup.bin", std::ios::binary);
        CheckOutputFile(foutGroup);
        CreatingListByGroup(finGroup, foutGroup, group);
        finGroup.close();
        foutGroup.close();

        std::ifstream finForSort("studentgroup.bin", std::ios::binary);
        CheckInputFile(finForSort);
        std::ofstream foutGroupSort("studentgrupsort.bin", std::ios::binary);
        CheckOutputFile(foutGroupSort);
        SortGroupByAlphabet(finForSort, foutGroupSort);
        finForSort.close();
        foutGroupSort.close();

        std::ifstream finForAvg("studentavg.bin", std::ios::binary);
        CheckInputFile(finForAvg);
        std::ofstream foutAvgNoSort("studentavggroup.bin", std::ios::binary);
        CheckOutputFile(foutAvgNoSort);
        CreatingListByAvg(finForAvg, foutAvgNoSort, group);
        finForAvg.close();
        foutAvgNoSort.close();

        std::ifstream finAvgNoSort("studentavggroup.bin", std::ios::binary);
        CheckInputFile(finAvgNoSort);
        std::ofstream foutAvgSort("studentavggroupsort.bin", std::ios::binary);
        CheckOutputFile(foutAvgSort);
        SortGroupByAvg(finAvgNoSort, foutAvgSort);
        finAvgNoSort.close();
        foutAvgSort.close();

        std::ifstream finExcellent("studentavg.bin", std::ios::binary);
        CheckInputFile(finExcellent);
        std::ofstream foutNoExcellent("excellentstudent.bin", std::ios::binary);
        CheckOutputFile(foutNoExcellent);
        SearchingExcellentStudent(finExcellent, foutNoExcellent);
        finExcellent.close();
        foutNoExcellent.close();

        std::ifstream finExcellentNoSort("excellentstudent.bin", std::ios::binary);
        CheckInputFile(finExcellentNoSort);
        std::ofstream foutExcellentSort("excellentstudentsort.bin", std::ios::binary);
        CheckOutputFile(foutExcellentSort);
        SortExcellent(finExcellentNoSort, foutExcellentSort);
        finExcellentNoSort.close();
        foutExcellentSort.close();

        std::ifstream finConvGroup("studentgrupsort.bin", std::ios::binary);
        CheckInputFile(finConvGroup);
        std::ofstream foutConvGroup("studentgroupsort.txt");
        CheckOutputFile(foutConvGroup);
        PrintConsoleForGroup(finConvGroup);
        MakeTxtForGroup(finConvGroup, foutConvGroup);
        finConvGroup.close();
        foutConvGroup.close();

        std::ifstream finConvAvg("studentavggroupsort.bin", std::ios::binary);
        CheckInputFile(finConvAvg);
        std::ofstream foutConvAvg("studentavggroupsort.txt");
        CheckOutputFile(foutConvAvg);
        PrintConsoleForAvg(finConvAvg);
        MakeTxtForAvg(finConvAvg, foutConvAvg);
        finConvAvg.close();
        foutConvAvg.close();

        std::ifstream finConvExcellent("excellentstudentsort.bin", std::ios::binary);
        CheckInputFile(finConvExcellent);
        std::ofstream foutConvExcellent("excellentstudentsort.txt");
        CheckOutputFile(foutConvExcellent);
        PrintConsoleForExcellent(finConvExcellent);
        MakeTxtForExcellent(finConvExcellent, foutConvExcellent);
        finConvExcellent.close();
        foutConvExcellent.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Îøèáêà: " << e.what();
    }
    return 0;
}