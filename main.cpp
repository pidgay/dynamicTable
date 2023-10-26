#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

class Data {
public:
    int number{};
    char character{};

    void update(int newNumber, char newCharacter) {
        number = newNumber;
        character = newCharacter;
    }

    void display() {
        cout
                << "Number: " << number << "    "
                << "Character: " << character << endl;
    }

    bool isBigger(Data* element) {
        if(element == nullptr){
            return false;
        }
        return number < element->number ? false : true;
    }

    Data() {
        number = 1 + rand() % 10000;
        character = 'A' + (rand() % 26);
    }
};

template <class T>
class DynamicArray {
public:
    int arraySize = {};
    int numberOfElements = {};
    T* arrayPointer = nullptr;
    float resizeMultiplier = {};
    int firstAvailableIndex = {};

    DynamicArray() {
        arraySize = 1;
        arrayPointer = new T[1];
        numberOfElements = 0;
        resizeMultiplier = 2.0;
        firstAvailableIndex = 0;
    }

    ~DynamicArray() {
        delete [] arrayPointer;
    }

    void resizeArray() {
        int arrayNewSize = arraySize * resizeMultiplier;
        T* tempPointer = new T[arrayNewSize];

        for (int i = 0; i < arraySize; ++i) {
            tempPointer[i] = arrayPointer[i];
        }
        delete arrayPointer;
        arraySize = arrayNewSize;
        arrayPointer = tempPointer;
    }

    void addNewElement(T* newElement) {
        if(firstAvailableIndex >= arraySize) { resizeArray(); }

        arrayPointer[firstAvailableIndex] = *newElement;
        firstAvailableIndex++;
        numberOfElements++;
    }

    bool checkIndex(int index){
        return (index < 0 || index >= arraySize) ? true : false;
    }

    T* returnElement(int index) {
        return checkIndex(index) ? arrayPointer[index] : nullptr;
    }

    bool updateElement(int index, int newNumber, char newCharacter) {
        if(checkIndex(index) == false) { return false; }
        arrayPointer[index].update(newNumber,newCharacter);
        return true;
    }

    void printArrayInfo() {
        if(arraySize == 0) {
            cout << "List is empty" << endl;
            return;
        }
        int quantityOfElementsToDisplay = 10;
        if (arraySize< 10) quantityOfElementsToDisplay = arraySize;

        cout << "    First elements: " << endl;
        for (size_t i = 0; i < quantityOfElementsToDisplay; ++i) {
            arrayPointer[i].display();
        }

        cout << "================================================================================" << endl;
        cout << "    Last elements: " << endl;
        for (size_t i = arraySize - quantityOfElementsToDisplay; i < arraySize; i++) {
            arrayPointer[i].display();
        }
    }

    void bubbleSort() {
        T* tempPointer;
        bool swapped;
        for (int i = 0; i < arraySize - 1; ++i) {
            swapped = false;
            for (int j = 0; j < arraySize - i - 1; ++j) {
                if (arrayPointer[j].isBigger(&arrayPointer[j + 1])) {
                    swap(arrayPointer[j], arrayPointer[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {break;}
        }
    }

    void clearArray() {
        delete arrayPointer;
        arrayPointer = new T[arraySize];
        firstAvailableIndex = 0;
    }
};

int main() {
    srand(time(nullptr));
    clock_t timeBefore, timeAfter, timeTaken, avgTime;
    clock_t timeBeforeOperation, timeAfterOperation;
    double timeOfSingleOperation;
    double worstTimeOfSingleOperation = 0.0;
    const int MAX_ORDER = 3;

    class DynamicArray<Data>* array = new DynamicArray<Data>; // Creating a new Dynamic Array

    timeBefore = clock();
    for (int i = 0; i < pow(10,MAX_ORDER); ++i) { // Adding new random elements
        class Data* newElement = new Data();
        timeBeforeOperation = clock();
        array->addNewElement(newElement);
        timeAfterOperation = clock();
        timeOfSingleOperation = timeAfterOperation - timeBeforeOperation;
        if (timeOfSingleOperation > worstTimeOfSingleOperation){
            worstTimeOfSingleOperation = timeOfSingleOperation / 1000;
            cout << "New worst time of single operation: " << worstTimeOfSingleOperation << "s" << " at index No. " << i << endl;
        }
    }
    timeAfter = clock();

    timeTaken = (timeAfter - timeBefore);
    avgTime = timeTaken / array->arraySize;
    //Printing array info and time taken
    cout << "================================================================================" << endl;
    cout << "    ADDING RANDOM ELEMENTS" << endl;
    cout << "================================================================================" << endl;
    cout
         << "Array size " << array->arraySize
         << "    " << "Total time:  " << timeTaken / 1000 << "s" <<"    " << "Avg. time: " << avgTime << "ns" << endl;
    cout << "================================================================================" << endl;
    array->printArrayInfo();

    cout << "================================================================================" << endl;
    cout << "    BUBBLE SORT" << endl;
    cout << "================================================================================" << endl;
    array->bubbleSort();
    array->printArrayInfo();

    array->clearArray();
    delete array;
    return 0;
}
