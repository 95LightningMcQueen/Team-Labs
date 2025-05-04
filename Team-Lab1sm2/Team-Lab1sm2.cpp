#include <iostream>
#include <cstdint>
#include <cmath>

const int32_t MAX_SIZE = 100;

void InputArraySize(int32_t& size);
bool CheckSize(int32_t size);

template <typename T>
void InputArray(T* array, int32_t size) 
{
    std::cout << "Input " << size << " elements of the array: ";
    for (int32_t i = 0; i < size; ++i) 
    {
        std::cin >> array[i];
    }
}

template <typename T>
void PrintArray(const T* array, int32_t size) 
{
    for (int32_t i = 0; i < size; ++i) 
    {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';
}

template <typename T>
int32_t FindElement(const T* array, int32_t size, T target) 
{
    for (int32_t i = 0; i < size; ++i) 
    {
        if (array[i] == target) 
        {
            return i + 1;
        }
    }
    return -1;
}

int32_t MaxElementPosition(const int32_t* array, int32_t size);
int32_t MinElementPosition(const int32_t* array, int32_t size);

template <typename T>
double CalculateAverage(const T* array, int32_t size, int32_t maxPos, int32_t minPos) 
{
    maxPos -= 1;
    minPos -= 1;

    if (maxPos == minPos || abs(maxPos - minPos) == 1) 
    {
        return -1;
    }

    int32_t start = std::min(minPos, maxPos);
    int32_t end = std::max(minPos, maxPos);

    double sum = 0;
    int32_t count = 0;
    for (int32_t i = start + 1; i < end; ++i) 
    {
        sum += array[i];
        count++;
    }

    return count > 0 ? sum / count : -1;
}

int32_t isPrime(int32_t num);
void PrimeNumbers(const int32_t* array, int32_t size);
int32_t SumOfPrimes(const int32_t* array, int32_t size);

void ReverseArray(int32_t* array, int32_t size);
int32_t DeleteNegativeNumbersFromArray(int32_t* array, int32_t size);

template <typename T>
int32_t CountElements(const T* array, int32_t size) 
{
    int32_t firstZero = -1;
    int32_t lastZero = -1;
    for (int32_t i = 0; i < size; ++i) 
    {
        if (array[i] == 0) 
        {
            if (firstZero == -1) firstZero = i;
            lastZero = i;
        }
    }
    return (firstZero != -1 && firstZero != lastZero)
        ? lastZero - firstZero - 1 : -1;
}

template <typename T>
void BubbleSort(T* array, int32_t size, bool ascending = true) 
{
    for (int32_t i = 0; i < size - 1; ++i) 
    {
        for (int32_t j = 0; j < size - i - 1; ++j) 
        {
            if ((ascending && array[j] > array[j + 1]) || (!ascending && array[j] < array[j + 1])) 
            {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

int main() 
{
    int32_t array[MAX_SIZE], size = 0, target = 0;

    InputArraySize(size);
    if (!CheckSize(size)) 
    {
        std::cerr << "Error: Invalid array size. Must be between 1 and " << MAX_SIZE << "\n";
        return 1;
    }

    InputArray(array, size);

    std::cout << "Your Array: ";
    PrintArray(array, size);

    std::cout << "\nInput target element to find: ";
    if (!(std::cin >> target)) 
    {
        std::cout << "Error: Invalid input\n";
        return 1;
    }

    int32_t result = FindElement(array, size, target);
    if (result != -1) 
    {
        std::cout << "First occurrence of element " << target << " is at position: " << result << '\n';
    }
    else 
    {
        std::cout << "Element " << target << " not found\n";
    }

    int32_t maxPos = MaxElementPosition(array, size);
    int32_t minPos = MinElementPosition(array, size);
    double average = CalculateAverage(array, size, maxPos, minPos);

    std::cout << "\nMax element: " << array[maxPos - 1] << " at position: " << maxPos << '\n';
    std::cout << "Min element: " << array[minPos - 1] << " at position: " << minPos << '\n';

    if (average != -1) 
    {
        std::cout << "Average between min and max: " << average << '\n';
    }
    else 
    {
        std::cout << "No elements between min and max (they are adjacent or the same).\n";
    }

    PrimeNumbers(array, size);
    std::cout << "Sum of prime numbers: " << SumOfPrimes(array, size) << '\n';

    ReverseArray(array, size);
    std::cout << "\nReversed Array: ";
    PrintArray(array, size);

    size = DeleteNegativeNumbersFromArray(array, size);
    std::cout << "Array without negatives: ";
    PrintArray(array, size);

    char order;
    std::cout << "\nSort in ascending order? (y/n): ";
    std::cin >> order;
    bool ascending = (order == 'y' || order == 'Y');
    BubbleSort(array, size, ascending);
    std::cout << "Sorted Array: ";
    PrintArray(array, size);

    int32_t countBetweenZeros = CountElements(array, size);
    if (countBetweenZeros != -1) 
    {
        std::cout << "\nCount of elements between first and last zeros: " << countBetweenZeros << '\n';
    }
    else 
    {
        std::cout << "\nNo two different zeros found in array\n";
    }

    return 0;
}

void InputArraySize(int32_t& size) 
{
    std::cout << "Input size of array: ";
    std::cin >> size;
}

bool CheckSize(int32_t size) 
{
    return size > 0 && size <= MAX_SIZE;
}

int32_t MaxElementPosition(const int32_t* array, int32_t size) 
{
    int32_t maxPos = 0;
    for (int32_t i = 1; i < size; ++i) 
    {
        if (array[i] > array[maxPos]) 
        {
            maxPos = i;
        }
    }
    return maxPos + 1;
}

int32_t MinElementPosition(const int32_t* array, int32_t size) 
{
    int32_t minPos = 0;
    for (int32_t i = 1; i < size; ++i) 
    {
        if (array[i] < array[minPos]) 
        {
            minPos = i;
        }
    }
    return minPos + 1;
}

int32_t isPrime(int32_t num) 
{
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;

    for (int32_t i = 5; i * i <= num; i += 6) 
    {
        if (num % i == 0 || num % (i + 2) == 0) 
        {
            return 0;
        }
    }
    return 1;
}

void PrimeNumbers(const int32_t* array, int32_t size) 
{
    std::cout << "Prime numbers: ";
    for (int32_t i = 0; i < size; ++i) 
    {
        if (isPrime(array[i])) {
            std::cout << array[i] << ' ';
        }
    }
    std::cout << '\n';
}

int32_t SumOfPrimes(const int32_t* array, int32_t size)
{
    int32_t sum = 0;
    for (int32_t i = 0; i < size; ++i) 
    {
        if (isPrime(array[i])) 
        {
            sum += array[i];
        }
    }
    return sum;
}

void ReverseArray(int32_t* array, int32_t size) 
{
    for (int32_t i = 0; i < size / 2; ++i) 
    {
        std::swap(array[i], array[size - 1 - i]);
    }
}

int32_t DeleteNegativeNumbersFromArray(int32_t* array, int32_t size) 
{
    int32_t newSize = 0;
    for (int32_t i = 0; i < size; ++i) 
    {
        if (array[i] >= 0) 
        {
            array[newSize++] = array[i];
        }
    }
    return newSize;
}