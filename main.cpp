#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_STUDENTS = 500;   // declare array size, larger to account for unknown file size

// Struct for Student ID and scores
struct Student {
    string id;
    double score;
};

// function prototypes
bool readData(const string& filename, Student students[], int& count);
void selectionSortID(Student students[], int count);
bool writeData(const string& filename, const Student students[], int count);


int main() {
    // create dynamic array for students
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    string inputFilename = "210-lab-13-grades.txt";
    string outputFilename = "210-lab-13-grades-sorted.txt";


    // try to read file first
    if (!readData(inputFilename, students, studentCount)) {
        return 1;
    }
    cout << "Read " << studentCount << " student records" << endl;

    // selection sort on student ids
    selectionSortID(students, studentCount);

    // save the sorted data in a new text file
    if (!writeData(outputFilename, students, studentCount)) {
        return 1;
    }
    cout << "Sorted results written to " << outputFilename << endl;


    return 0;
}

// funcion definition for readData
bool readData(const string& filename, Student students[], int& count) {
    ifstream inFile(filename);

    // check if file opens
    if (!inFile) {
        cout << "Error: Could not open input file " << filename << endl;
        return false;
    }
    
    count = 0;
    // loop through the data file until the end or array if filled
    while (count < MAX_STUDENTS && inFile >> students[count].id >> students[count].score){
        count++;
    }
    inFile.close();
    return true;

}

// function definition for selectionSortID
void selectionSortID(Student students[], int count) {
    // selection sort looks for smallest ID each time
    for (int i = 0; i < count; i++) {
        int minIndex = i;

        //find the smallest ID in the rest of the array
        for (int j = i + 1; j < count; j++) {
            if (students[j].id < students[minIndex].id) {
                minIndex = j;
            }
        }

        //swap the elements if smaller ID found
        if (minIndex != i) {

            Student temp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = temp;
        }
    }
}

// function definition for writeData
bool writeData(const string& filename, const Student students[], int count) {
    ofstream outFile(filename);

    // double check if output file opened
    if (!outFile) {
        cout << "Error: could not open output file " << filename << endl;
        return false;
    }

    //print each student record
    for (int i = 0; i < count; i++) {
        outFile << students[i].id << " " << students[i].score << "\n";
    }
    outFile.close();
    return true;
}