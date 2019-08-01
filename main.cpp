#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

//Declaring a global data structure for the student
struct Student{
    string fName;
    string lName;
    double average;
    int max;
    int min;
};

//Online processing of the data from the file via structure implementation

//Global variables
const string FILENAME = "NamesGrades.txt"; //file that we read

//Function Declarations
//Reference operator specified because vectors are not passed by reference automatically

void loadStudents(vector<Student> &students, string filename);
void displayAvgTemp(vector<Student> &students);
void displayMinTemp(vector<Student> &students);
void displayMaxTemp(vector<Student> &students);
string getGradeLetter(int grade);
int getLongestNameLength(const vector<Student> &students);
void swap(Student &a, Student &b);
void bubbleSort(vector<Student> &students, bool(*doSwapTest)(Student&, Student&));
bool doAvgSwapTest(Student &first, Student &second);
bool doMaxSwapTest(Student &first, Student &second);
bool doMinSwapTest(Student &first, Student &second);

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}