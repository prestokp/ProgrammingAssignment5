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

    vector<Student> students; //Student collection
    char choice;

    //Getting the student data from the file
    try{
        loadStudents(students, FILENAME);
    }
    //Catch exception if file fetch fails
    catch (const char* message){
        cout << message << endl;
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    //Do-While Loop
    do{
        //Present Menu
        cout << "\nStudent Report Program\n\n"
            << "\t1. Display Average Grade\n"
            << "\t2. Display Maximum Grade\n"
            << "\t3. Display Minimum Grade\n"
            << "\t4. Display Student Roll\n"
            << "\t5. Exit Program\n\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        //Clearing out the stream buffer
        while (getchar() != '\n');

        //Process the choice
        switch (choice)
        {

            case '1': //Average
                displayAvgTemp(students);
                break;

            case '2': //Maximum
                displayMaxTemp(students);
                break;

            case '3': //Minimum
                displayMinTemp(students);

            case '4': //Roll Call
                //Display the student roll call
                return 0;

            case '5': //Quits the program
                break;


        }//End of switch statement


    }while(choice != '4');


    return 0;
}