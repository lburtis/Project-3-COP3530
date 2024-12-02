#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <array>

using namespace std;

// Global variable that tracks # of comparisons made
int comparisonCount = 0;

// ------------Merge Sort Implementation ------------
// Helper function to merge two sorted halves of the array
void merge(int* numbers, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Temporary arrays to hold halves
    int* left_half = new int[left_size];
    int* right_half = new int[right_size];

    // Copy data to temporary left array
    for (int i = 0; i < left_size; ++i) {
        left_half[i] = numbers[left + i];
    }

    // Copy data to temporary right array
    for (int i = 0; i < right_size; ++i) {
        right_half[i] = numbers[mid + 1 + i];
    }

    // Merges temporary arrays together as vector

    // Initial index of left half
    int i = 0;

    // Initial index of right half
    int j = 0;

    // Initial index of merged array
    int k = left;

    while (i < left_size && j < right_size) {
        comparisonCount++;
        if (left_half[i] <= right_half[j]) {
            numbers[k] = left_half[i];
            i++;
        }
        else {
            numbers[k] = right_half[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left_half
    while (i < left_size) {
        numbers[k] = left_half[i];
        i++;
        k++;
    }

    // Copy remaining elements of right_half
    while (j < right_size) {
        numbers[k] = right_half[j];
        j++;
        k++;
    }

    // Free allocated memory
    delete[] left_half;
    delete[] right_half;
}

// Recursively sorts array data using merge sort algorithm
void mergeSort(int* numbers, int left, int right) {
    if (left < right) {
        // Finds the middle point
        int mid = left + (right - left) / 2;

        // Recursively sort both halves
        mergeSort(numbers, left, mid);
        mergeSort(numbers, mid + 1, right);

        // Merge the sorted halves
        merge(numbers, left, mid, right);
    }
}

// ------------ Quick Sort Implementation -------------

// Function to partition the array for QuickSort
int partition(int* arr, int low, int high) {
    // Choose the last element as pivot
    int pivot = arr[high];

    // i is the index of the smaller element
    int i = low - 1;

    for (int j = low; j < high; j++) {

        comparisonCount++;

        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Function to perform QuickSort
void quickSort(int* arr, int low, int high) {
    int* stack = new int[high - low + 1];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pi = partition(arr, low, high);

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }

    delete[] stack;
}


// ------------ File Handling Functions -----------

// Reads data from file and stores in array
void readFile(const string& filename, int* numbers) {

    // Opens file
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    int index = 0;

    // Reads integers from file and stores them
    while (inputFile >> numbers[index] && index < 100000) {
        index++;
    }

    // Close the file
    inputFile.close();
}

// Prints array data to file
void printData(const string& filename, const int* numbers) {
    // Opens output file
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    // Writes each array entry to its own line
    for (int i = 0; i < 100000; ++i) {
        outputFile << numbers[i] << '\n';
    }

    // Close the file
    outputFile.close();
}

int main() {
    // Stores location of files to read
    const string sorted_input = "files/sorted_numbers.txt";
    const string reverse_input = "files/reverse_numbers.txt";
    const string random_input = "files/random_numbers.txt";


    // Stores location of files to print data to
    const string merge_sorted_output = "files/merge_sorted_numbers_output.txt";
    const string merge_reverse_output = "files/merge_reverse_numbers_output.txt";
    const string merge_random_output = "files/merge_random_numbers_output.txt";

    const string quick_sorted_output = "files/quick_sorted_numbers_output.txt";
    const string quick_reverse_output = "files/quick_reverse_numbers_output.txt";
    const string quick_random_output = "files/quick_random_numbers_output.txt";


    // Allocate arrays on the heap
    int* sorted_merge = new int[100000];
    int* reverse_merge = new int[100000];
    int* random_merge = new int[100000];

    int* sorted_quick = new int[100000];
    int* reverse_quick = new int[100000];
    int* random_quick = new int[100000];


    // Reads each file into arrays
    readFile(sorted_input, sorted_merge);
    readFile(reverse_input, reverse_merge);
    readFile(random_input, random_merge);

    readFile(sorted_input, sorted_quick);
    readFile(reverse_input, reverse_quick);
    readFile(random_input, random_quick);

    int size_of_array = 100000;


    // Merge sorts data of vectors, calculates elapsed sort time, and # of comparisons made
    auto start = chrono::high_resolution_clock::now();
    mergeSort(sorted_merge, 0, size_of_array - 1);
    auto end = chrono::high_resolution_clock::now();
    auto merge_sorted_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int merge_sorted_comparisons = comparisonCount;
    comparisonCount = 0;

    start = chrono::high_resolution_clock::now();
    mergeSort(reverse_merge, 0, size_of_array - 1);
    end = chrono::high_resolution_clock::now();
    auto merge_reverse_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int merge_reverse_comparisons = comparisonCount;
    comparisonCount = 0;

    start = chrono::high_resolution_clock::now();
    mergeSort(random_merge, 0, size_of_array - 1);
    end = chrono::high_resolution_clock::now();
    auto merge_random_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int merge_random_comparisons = comparisonCount;
    comparisonCount = 0;


    // Quick sorts data of vectors, calculates elapsed sort time, and # of comparisons made
    start = chrono::high_resolution_clock::now();
    quickSort(sorted_quick, 0, size_of_array - 1);
    end = chrono::high_resolution_clock::now();
    auto quick_sorted_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int quick_sorted_comparisons = comparisonCount;
    comparisonCount = 0;

    start = chrono::high_resolution_clock::now();
    quickSort(reverse_quick, 0, size_of_array - 1);
    end = chrono::high_resolution_clock::now();
    auto quick_reverse_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int quick_reverse_comparisons = comparisonCount;
    comparisonCount = 0;

    start = chrono::high_resolution_clock::now();
    quickSort(random_quick, 0, size_of_array - 1);
    end = chrono::high_resolution_clock::now();
    auto quick_random_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int quick_random_comparisons = comparisonCount;
    comparisonCount = 0;


    // Prints arrays to files
    printData(merge_sorted_output, sorted_merge);
    printData(merge_reverse_output, reverse_merge);
    printData(merge_random_output, random_merge);

    printData(quick_sorted_output, sorted_quick);
    printData(quick_reverse_output, reverse_quick);
    printData(quick_random_output, random_quick);


    // Prints comparison and duration info to console
    // Merge Sort
    cout << "-----------------------------------" << endl;
    cout << endl;
    cout << "** Merge Sort Results **" << endl;
    cout << "Sorted List:\n";
    cout << "# of Comparisons: " << merge_sorted_comparisons << endl;
    cout << "Elapsed Time: " << merge_sorted_duration << " microseconds" << endl;
    cout << endl;
    cout << "Reverse List:\n";
    cout << "# of Comparisons: " << merge_reverse_comparisons << endl;
    cout << "Elapsed Time: " << merge_reverse_duration << " microseconds" << endl;
    cout << endl;
    cout << "Random List:\n";
    cout << "# of Comparisons: " << merge_random_comparisons << endl;
    cout << "Elapsed Time: " << merge_random_duration << " microseconds" << endl;
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;

    // Quick Sort
    cout << "** Quick Sort Results **" << endl;
    cout << "Sorted List:\n";
    cout << "# of Comparisons: " << quick_sorted_comparisons << endl;
    cout << "Elapsed Time: " << quick_sorted_duration << " microseconds" << endl;
    cout << endl;
    cout << "Reverse List:\n";
    cout << "# of Comparisons: " << quick_reverse_comparisons << endl;
    cout << "Elapsed Time: " << quick_reverse_duration << " microseconds" << endl;
    cout << endl;
    cout << "Random List:\n";
    cout << "# of Comparisons: " << quick_random_comparisons << endl;
    cout << "Elapsed Time: " << quick_random_duration << " microseconds" << endl;
    cout << endl;
    cout << "-----------------------------------" << endl;

    // Deletes excess memory
    delete[] sorted_merge;
    delete[] reverse_merge;
    delete[] random_merge;

    delete[] sorted_quick;
    delete[] reverse_quick;
    delete[] random_quick;

    return 0;
}
