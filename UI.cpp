#include "Heap.h"
#include "PriorityQueue.h"
#include "UI.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

std::string selectTypeOfClass();
std::string selectTypeOfElements();

template <typename T>
class UserHeap {
private:
    Heap<T>* heap;
    char rootLeft;
    char rootRight;
    char firstLeft;
    char firstRight;
    char secondLeft;
    char secondRight;
    std::string order; // в каком порядке выводить Root, First, Second (Пример: FRS)


    void printRoot(int index, Heap<T>* heap) {
        std::cout << rootLeft << heap->get(index) << rootRight;
    }

    void printLeft(int index, Heap<T>* heap) {
        if (index * 2 + 1 < heap->getSize()) {
            std::cout << firstLeft;
            print(index * 2 + 1, heap);
            std::cout << firstRight;
        }
    }

    void printRight(int index, Heap<T>* heap) {
        if (index * 2 + 2 < heap->getSize()) {
            std::cout << secondLeft;
            print(index * 2 + 2, heap);
            std::cout << secondRight;
        }
    }

    void print(int index, Heap<T>* heap) {
        if (order == "RSF") {
            printRoot(index, heap);
            printRight(index, heap);
            printLeft(index, heap);
        }
        if (order == "RFS") {
            printRoot(index, heap);
            printLeft(index, heap);
            printRight(index, heap);
        }
        if (order == "FSR") {
            printLeft(index, heap);
            printRight(index, heap);
            printRoot(index, heap);
        }
        if (order == "FRS") {
            printLeft(index, heap);
            printRoot(index, heap);
            printRight(index, heap);
        }
        if (order == "SFR") {
            printRight(index, heap);
            printLeft(index, heap);
            printRoot(index, heap);
        }
        if (order == "SRF") {
            printRight(index, heap);
            printRoot(index, heap);
            printLeft(index, heap);
        }
    }

    void outputFormat() {
        std::string format;
        std::cout << "Enter the format of heap without any blank. Example: {Root}(Left)[Right].\n";
        std::cin >> format;
        while (format.find("Root") == -1 || format.find("Left") == -1 || format.find("Right") == -1) {
            std::cout << "Entered format is invalid. Try again.\n";
            std::cin >> format;
        }
        rootLeft = format[format.find("Root") - 1];
        rootRight = format[format.find("Root") + 4];
        firstLeft = format[format.find("Left") - 1];
        firstRight = format[format.find("Left") + 4];
        secondLeft = format[format.find("Right") - 1];
        secondRight = format[format.find("Right") + 5];
        if (format.find("Root") < format.find("Right") && format.find("Right") < format.find("Left")) order = "RSF";
        else if (format.find("Root") < format.find("Left") && format.find("Left") < format.find("Right")) order = "RFS";
        else if (format.find("Left") < format.find("Right") && format.find("Right") < format.find("Root")) order = "FSR";
        else if (format.find("Left") < format.find("Root") && format.find("Root") < format.find("Right")) order = "FRS";
        else if (format.find("Right") < format.find("Left") && format.find("Left") < format.find("Root")) order = "SFR";
        else order = "SRF";
    }

    void initialize() {
        int n;
        std::cout << "Enter the quantity of elements you want to full the heap: ";
        std::cin >> n;
        while (n < 0) {
            std::cout << "Entered number is less than 0. Try again.\n";
            std::cin >> n;
        }

        if (n > 0) {
            std::cout << "Enter the elements you want to be in your heap: ";
            int current = 0;
            T item;
            while (current < n) {
                std::cin >> item;
                heap->insert(item);
                ++current;
            }
        }
    }

public:
    UserHeap() {
        std::cout<< "Enter the type of heap you want to create. Enter 'max' or 'min': ";
        std::string compareWord;
        std::cin >> compareWord;
        while (compareWord != "min" && compareWord != "max") {
            std::cout << "You entered the invalid word. Try again.\n";
            std::cin >> compareWord;
        }
        if (compareWord == "max") heap = new Heap<T>("max");
        else heap = new Heap<T>("min");

        initialize();
        outputFormat();
    }

    ~UserHeap() {
        delete heap;
    }

    void getSize() {
        std::cout << heap->getSize() << "\n";
    }

    void printHeap() {
        if (heap->getSize() == 0) {
            std::cout << "The heap is empty.\n";
            return;
        }

        print(0, heap);
        std::cout << "\n";
    }

    void insert() {
        std::cout << "Enter the element you want to insert: ";
        T item;
        std::cin >> item;
        heap->insert(item);
        std::cout << "The item was inserted.\n";
    }

    void deleteRoot() {
        if (heap->getSize() == 0) {
            std::cout << "The heap is empty now.\n";
            return;
        }
        heap->deleteRoot();
        std::cout << "The root is deleted.\n";
    }

    void find() {
        std::cout << "Enter the element you want to find: ";
        T item;
        std::cin >> item;
        if (heap->find(item) == -1) {
            std::cout << "The element wasn't found in heap.\n";
        } else {
            std::cout << "The element was found in heap.\n";
        }
    }

    void printSubHeap() {
        std::cout << "Enter the root of the heap: ";
        T item;
        std::cin >> item;
        Heap<T>* subTree;
        try {
            subTree = heap->extractSubTree(item);
            print(0, subTree);
            std::cout << "\n";
            delete subTree;
        } catch (std::invalid_argument& ex) {
            std::cout << ex.what();
        }
    }

    void findSubTree() {
        std::cout << "Enter the size of subTree: ";
        int n;
        std::cin >> n;
        T subTree[n];
        std::cout << "Enter the elements of subTree: ";
        int current = 0;
        while (current < n) {
            std::cin >> subTree[current];
            ++current;
        }
        if (heap->findSubTree(subTree, n)) {
            std::cout << "The subTree was found.\n";
        } else {
            std::cout << "The subTree wasn't found.\n";
        }
    }

    void merge() {
        std::cout << "Enter the size of other heap: ";
        int n;
        std::cin >> n;
        T other[n];
        int current = 0;
        while (current < n) {
            std::cin >> other[current];
            ++current;
        }
        Heap<T> otherHeap(heap->getCompareType(), other, n);
        Heap<T>* result = heap->merge(otherHeap);
        delete heap;
        heap = result;
    }
};


template <typename T>
class HeapUI {
public:

    void startHeap() {
        UserHeap<T> userHeap;
        std::string command;

        std::cout << "\nThere are the commands you may commit:\n"
            << "getSize,\n"
            << "printHeap,\n"
            << "printSubHeap,\n"
            << "insert,\n"
            << "deleteRoot,\n"
            << "merge,\n"
            << "find,\n"
            << "findSubTree,\n"
            << "deleteHeap.\n\n";
        while (true) {
            std::cout << "Enter the command: ";
            std::cin >> command;
            if (command == "getSize") userHeap.getSize();
            else if (command == "printHeap") userHeap.printHeap();
            else if (command == "printSubHeap") userHeap.printSubHeap();
            else if (command == "insert") userHeap.insert();
            else if (command == "deleteRoot") userHeap.deleteRoot();
            else if (command == "merge") userHeap.merge();
            else if (command == "find") userHeap.find();
            else if (command == "findSubTree") userHeap.findSubTree();
            else if (command == "deleteHeap") break;
            else std::cout << "The invalid command.\n";
        }
    }
};


template <typename T>
class UserQueue {
private:
    PriorityQueue<T>* queue;

public:
    UserQueue() {
        queue = new PriorityQueue<T>;
        int n;
        std::cout << "Enter the quantity of elements you want to full the queue: ";
        std::cin >> n;
        while (n < 0) {
            std::cout << "Entered number is less than 0. Try again.\n";
            std::cin >> n;
        }

        if (n > 0) {
            std::cout << "Enter the elements you want to be in your queue: ";
            int current = 0;
            T item;
            while (current < n) {
                std::cin >> item;
                queue->insert(item);
                ++current;
            }
        }
    }

    ~UserQueue() {
        delete queue;
    }

    void printQueue() {
        if (queue->getSize() == 0) {
            std::cout << "The queue is empty.\n";
            return;
        }

        PriorityQueue<T> copy = *queue;
        for (int i = 0; i < queue->getSize(); ++i) {
            std::cout << copy.extractRoot();
            copy.deleteRoot();
        }
        std::cout << "\n";
    }

    void insert() {
        T item;
        std::cout << "Enter the element you want to insert: ";
        std::cin >> item;
        queue->insert(item);
        std::cout << "The item was inserted.\n";
    }

    void deleteRoot() {
        if (queue->getSize() == 0) {
            std::cout << "The queue is empty now.\n";
            return;
        }
        queue->deleteRoot();
        std::cout << "The root is deleted.\n";
    }

    void find() {
        std::cout << "Enter the element you want to find: ";
        T item;
        std::cin >> item;
        if (queue->find(item) == -1) {
            std::cout << "The element wasn't found in queue.\n";
        } else {
            std::cout << "The element was found in queue.\n";
        }
    }

    void getSize() {
        std::cout << queue->getSize() << "\n";
    }

    void findSubTree() {
        std::cout << "Enter the size of subTree: ";
        int n;
        std::cin >> n;
        T subTree[n];
        std::cout << "Enter the elements of subTree: ";
        int current = 0;
        while (current < n) {
            std::cin >> subTree[current];
            ++current;
        }
        if (queue->findSubTree(subTree, n)) {
            std::cout << "The subTree was found.\n";
        } else {
            std::cout << "The subTree wasn't found.\n";
        }
    }

    void printSubsequence() {
        std::cout << "Enter the startIndex and endIndex of queue.\n";
        int startIndex;
        int endIndex;
        std::cin >> startIndex >> endIndex;
        try {
            T* subSequence = queue->getSubsequence(startIndex, endIndex);
            for (int i = 0; i < endIndex - startIndex + 1; ++i) {
                std::cout << subSequence[i] << " ";
            }
            std::cout << "\n";
            delete[] subSequence;
        } catch (std::invalid_argument& ex) {
            std::cout << ex.what();
        }
    }


    void findSubsequence() {
        std::cout << "Enter the size of subsequence: ";
        int n;
        std::cin >> n;
        T subsequence[n];
        std::cout << "Enter the elements of subsequence: ";
        int current = 0;
        while (current < n) {
            std::cin >> subsequence[current];
            ++current;
        }

        if (queue->findSubsequence(subsequence, n) == 1) {
            std::cout << "The subsequence was found.\n";
        } else {
            std::cout << "The subsequence wasn't found.\n";
        }
    }
};


template <typename T>
class QueueUI {
public:

    void startQueue() {
        UserQueue<T> userQueue;
        std::string command;

        std::cout << "\nThere are the commands you may commit:\n"
            << "getSize,\n"
            << "printQueue,\n"
            << "printSubsequence,\n"
            << "insert,\n"
            << "deleteRoot,\n"
            << "find,\n"
            << "findSubTree,\n"
            << "findSubsequence,\n"
            << "deleteQueue.\n\n";
        while (true) {
            std::cout << "Enter the command: ";
            std::cin >> command;
            if (command == "getSize") userQueue.getSize();
            else if (command == "printQueue") userQueue.printQueue();
            else if (command == "printSubsequence") userQueue.printSubsequence();
            else if (command == "insert") userQueue.insert();
            else if (command == "deleteRoot") userQueue.deleteRoot();
            else if (command == "find") userQueue.find();
            else if (command == "findSubTree") userQueue.findSubTree();
            else if (command == "findSubsequence") userQueue.findSubsequence();
            else if (command == "deleteQueue") break;
            else std::cout << "The invalid command.\n";
        }
    }
};


std::string selectTypeOfClass() {
    std::cout << "Enter the name of class you want to work with (queue\\heap): ";
    std::string typeOfClass;
    std::cin >> typeOfClass;
    while (typeOfClass != "queue" && typeOfClass != "heap") {
        std::cout << "Entered word is invalid. Try again.\n";
        std::cin >> typeOfClass;
    }
    return typeOfClass;
}

std::string selectTypeOfElements() {
    std::cout << "Enter the type of elements in your class (int\\double\\string): ";
    std::string typeOfElements;
    std::cin >> typeOfElements;
    while (typeOfElements != "int" && typeOfElements != "double" && typeOfElements != "string") {
        std::cout << "Entered word is invalid. Try again.\n";
        std::cin >> typeOfElements;
    }
    return typeOfElements;
}

void startUI() {
    std::string nextAction;
    std::string typeOfClass;
    std::string typeOfElements;

    std::cout << "This is the start of program.\n";

    while (true) {
        typeOfClass = selectTypeOfClass();
        typeOfElements = selectTypeOfElements();
        if (typeOfClass == "heap" && typeOfElements == "int") {
            HeapUI<int> heapUI;
            heapUI.startHeap();
        } else if (typeOfClass == "heap" && typeOfElements == "double") {
            HeapUI<double> heapUI;
            heapUI.startHeap();
        } else if (typeOfClass == "heap" && typeOfElements == "string") {
            HeapUI<std::string> heapUI;
            heapUI.startHeap();
        } else if (typeOfClass == "queue" && typeOfElements == "int") {
            QueueUI<int> queueUI;
            queueUI.startQueue();
        } else if (typeOfClass == "queue" && typeOfElements == "double") {
            QueueUI<double> queueUI;
            queueUI.startQueue();
        } else if (typeOfClass == "queue" && typeOfElements == "string") {
            QueueUI<std::string> queueUI;
            queueUI.startQueue();
        }

        std::cout << "If you want to finish the program -> end,\n" << "If you want to restart -> again.\n";
        std::cin >> nextAction;
        while (nextAction != "end" && nextAction != "again") {
            std::cout << "The invalid input. Try again.\n";
            std::cin >> nextAction;
        }
        if (nextAction == "end") break;
    }
    std::cout << "The end of program.\n";
}






/* неудачный (со вполне ожидаемым результатом) эксперимент. Может быть, как-нибудь потом к нему вернусь.
void insert() {
    std::string type = typeid(T).name();
    if (type.find("Person") == 1) {
        std::cout << "Which type of person do you want to insert?\nTeacher -> teacher\nStudent->student.\n";
        std::string person;
        std::cin >> person;
        std::string student = "student";
        std::string teacher = "teacher";
        while ((person != student) != 0 && (person != teacher)) {
            std::cout << "Invalid input. Try again.\n";
            std::cin >> person;
        }
        if (person == student) {
            Student item;
        } else {
            Teacher item;
        }
    } else {
        T item;
    }
    ...
}
*/

