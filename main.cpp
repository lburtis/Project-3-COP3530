#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Global variable that tracks # of comparisons made
int comparisonCount = 0;

// Helper function to merge two sorted halves of the vector
void merge(vector<int>* numbers, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Temporary arrays to hold halves
    vector<int> left_half(left_size);
    vector<int> right_half(right_size);

    // Copy data to temporary left array
    for (int i = 0; i < left_size; ++i) {
        left_half[i] = (*numbers)[left + i];
    }

    // Copy data to temporary right array
    for (int i = 0; i < right_size; ++i) {
        right_half[i] = (*numbers)[mid + 1 + i];
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
            (*numbers)[k] = left_half[i];
            i++;
        }
        else {
            (*numbers)[k] = right_half[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left_half
    while (i < left_size) {
        (*numbers)[k] = left_half[i];
        i++;
        k++;
    }

    // Copy remaining elements of right_half
    while (j < right_size) {
        (*numbers)[k] = right_half[j];
        j++;
        k++;
    }
}


// Recursively sorts vector data using merge sort algorithm
void mergeSort(vector<int>* numbers, int left, int right) {
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


// Reads data from file and stores in vector
void readFile(const string& filename, vector<int>* numbers) {

    // Opens file
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    // Reads integers from file and stores them
    int number;
    while (inputFile >> number) {
        numbers->push_back(number);
    }

    // Close the file
    inputFile.close();
}


// Prints vector data to file
void printData(const string& filename, const vector<int>* numbers) {

    // Opens output file
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    // Writes each vector entry to its own line
    for (int i = 0; i < numbers->size(); ++i) {
        outputFile << (*numbers)[i] << '\n';
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
    const string sorted_output = "files/sorted_numbers_output.txt";
    const string reverse_output = "files/reverse_numbers_output.txt";
    const string random_output = "files/random_numbers_output.txt";

    // Declares each vector
    vector<int> sorted;
    vector<int> reverse;
    vector<int> random;

    // Reads each file to vector
    readFile(sorted_input, &sorted);
    readFile(reverse_input, &reverse);
    readFile(random_input, &random);

    // Sorts data of vectors, calculates elapsed sort time, and # of comparisons made
    auto start = chrono::high_resolution_clock::now();
    mergeSort(&sorted, 0, sorted.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto sorted_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int sorted_comparisons = comparisonCount;
    comparisonCount = 0;

    start = chrono::high_resolution_clock::now();
    mergeSort(&reverse, 0, reverse.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto reverse_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int reverse_comparisons = comparisonCount;
    comparisonCount = 0;

    start = chrono::high_resolution_clock::now();
    mergeSort(&random, 0, random.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto random_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int random_comparisons = comparisonCount;
    comparisonCount = 0;

    // Prints vector info to file
    printData(sorted_output, &sorted);
    printData(reverse_output, &reverse);
    printData(random_output, &random);

    cout << "Comparisons made in Sorted List: " << sorted_comparisons << endl;
    cout << "Elapsed Time for Sorted List: " << sorted_duration << " microseconds" << endl;

    cout << "Comparisons made in Reverse List: " << reverse_comparisons << endl;
    cout << "Elapsed Time for Reverse List: " << reverse_duration << " microseconds" << endl;

    cout << "Comparisons made in Random List: " << random_comparisons << endl;
    cout << "Elapsed Time for Random List: " << random_duration << " microseconds" << endl;

    return 0;
}