#include <iostream>
#include "header.h"
#include <fstream>
#include <climits>

using namespace std;

int main(int argc,char* argv[])
{   
    string algorithm, inputFile , outputFile;
    for (int i = 1; i < argc ;i++)
    {
        string temp = argv[i];
        if (temp == "-a" && i + 1 < argc)
        {
            algorithm = argv[i+1];
            i++;
        } else if (temp == "-i" && i + 1 < argc)
        {
            inputFile = argv[i + 1];
            i++;
        }
        else if (temp == "-o" && i + 1 < argc)
        {
            outputFile = argv[i + 1];
            i++;
        }
    }



    ifstream in(inputFile);
    if (!in)
    {
        cout << "Khong the mo file input" << endl;
        return 1;
    }

    int n;
    in >> n;
    in.ignore(1);

    int *a = new int[n];
    for (int i = 0; i < n ;i++)
    {   
        int temp;
        in >> temp;
        a[i] = temp;
    }

    in.close();

    if (algorithm == "selection-sort")
    {
        selectionSort(a,n);
    }
    else if (algorithm == "insertion-sort")
    {
        insertionSort(a,n);
    }
    else if (algorithm == "bubble-sort")
    {
        bubbleSort(a,n);
    }
    else if (algorithm == "merge-sort")
    {
        mergeSort(a,0,n - 1);
    }
    else if (algorithm == "heap-sort")
    {
        heapSort(a,n);
    }
    else if (algorithm == "quick-sort")
    {
        quickSort(a,0,n - 1);
    }
    else if (algorithm == "radix-sort")
    {
        radixSort(a,n);
    }
    else if (algorithm == "shaker-sort")
    {
        shakerSort(a,n);
    }
    else if (algorithm == "shell-sort")
    {
        shellSort(a,n);
    }
    else if (algorithm == "counting-sort")
    {
        countingSort(a,n);
    }
    else if (algorithm == "flash-sort")
    {
        flashSort(a,n);
    }
    else
    {
        cout << "Thuat toan khong hop le" << endl;
        return 0;
    }

    ofstream out(outputFile);
    if (!out)
    {
        cout << "Khong the mo file output" << endl;
        return 0;
    }
    out << n << endl;
    for (int i = 0; i < n ;i++)
    {
        out << a[i] << " ";
    }
    out.close();

    delete[] a;

    return 0;
}