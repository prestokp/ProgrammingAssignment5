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
void displayAvgGrade(vector<Student> &students);
void displayMinGrade(vector<Student> &students);
void displayMaxGrade(vector<Student> &students);
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
                displayAvgGrade(students);
                break;

            case '2': //Maximum
                displayMaxGrade(students);
                break;

            case '3': //Minimum
                displayMinGrade(students);

            case '4': //Roll Call
                //Display the student roll call
                return 0;

            case '5': //Quits the program
                break;

            default:
                cout << "Invalid Option. Please select again.\n\n";
                break;

        }//End of switch statement

        if (choice != '4'){
            cout << endl;
            system("PAUSE");
            system("CLS");
        }

    }while(choice != '4');

    cout << endl;

    return 0;

    //Load data from the file into the Student vector


}//Main function delimiter


void loadStudents(vector<Student> &students, string filename) {

    ifstream iFile; //input file stream
    int total = 0;  //accumulator for total students
    int max;        //max grade for the student
    int min;        //min grade for the student
    int currentGrade; //current grade for the student
    Student student; //a temp Student for getting data
    int numGrades = 0; //How many grades for each student

    //Open the file
    iFile.open(filename);
    if (!iFile){
        throw "Cannot open file " + filename;
    }

    //Read and process the file information
    while (iFile >> student.fName >> student.lName){

        //Get the first grade and place in total, max, and min
        //We'll work our way with grades from here
        iFile >> total;
        max = min = total;
        numGrades = 1;

        //Burns across the whitespace to the next numbers in the row
        while (iFile >> currentGrade){

            numGrades++;
            total += currentGrade;
            if (currentGrade > max) max = currentGrade;
            if (currentGrade < min) min = currentGrade;

        }//Inner while loop delimiter

        //Clear Fail
        iFile.clear();

        //averaging the grades out
        student.average = static_cast<double>(total)/numGrades;
        student.max = max;
        student.min = min;

        //refers to our collection of Students
        //push back is adding to the collection
        students.push_back(student);

    }//Outer while loop delimiter

    //Closing the file
    iFile.close();

}//load students function delimiter

//Displaying the average grade for students
void displayAvgGrade(vector<Student> &students) {

    //Get the longest name from the students for formatting purposes
    int maxLength = getLongestNameLength(students) + 1;

    cout << setprecision(1) << fixed << showpoint;

    //Setup table header
    cout << "\n\nGrade Averages\n";
    cout << setw(maxLength) << left << "Name"
        << setw(8) << right << "Average"
        << setw(10) << "Grade Letter" << endl;

    //Sort the students by their average
    bubbleSort(students, doAvgSwapTest);

    //Display the table
    for(int i = 0; i < students.size(); i++){

        //Setw is not sticky in the stream
        cout << setw(maxLength) << left
            << (students[i].fName + " " + students[i].lName);

        cout << setw(8) << right << students[i].average
            << setw(10) << getGradeLetter(students[i].average)
            << endl;
    }

}//Average grade function delimiter

void displayMinGrade(vector<Student> &students) {

    //Get the longest name from the students for formatting purposes
    int maxLength = getLongestNameLength(students) + 1;

    //cout << setprecision(1) << fixed << showpoint;

    //Setup table header
    cout << "\n\nMinimum Grade\n";
    cout << setw(maxLength) << left << "Name"
         << setw(8) << right << "Minimum"
         << setw(10) << "Grade Letter" << endl;

    //Sort the students by their minimum grade
    bubbleSort(students, doMinSwapTest);

    //Display the table
    for(int i = 0; i < students.size(); i++){

        //Setw is not sticky in the stream
        cout << setw(maxLength) << left
             << (students[i].fName + " " + students[i].lName);

        cout << setw(8) << right << students[i].min
             << setw(10) << getGradeLetter(students[i].min)
             << endl;
    }

}//Min grade function delimiter

void displayMaxGrade(vector<Student> &students) {

    //Get the longest name from the students for formatting purposes
    int maxLength = getLongestNameLength(students) + 1;

    //cout << setprecision(1) << fixed << showpoint;

    //Setup table header
    cout << "\n\nMaximum Grade\n";
    cout << setw(maxLength) << left << "Name"
         << setw(8) << right << "Maximum"
         << setw(10) << "Grade Letter" << endl;

    //Sort the students by their maximum grade
    bubbleSort(students, doMaxSwapTest);

    //Display the table
    for(int i = 0; i < students.size(); i++){

        //Setw is not sticky in the stream
        cout << setw(maxLength) << left
             << (students[i].fName + " " + students[i].lName);

        cout << setw(8) << right << students[i].max
             << setw(10) << getGradeLetter(students[i].max)
             << endl;
    }

}//Max grade function delimiter

string getGradeLetter(int grade) {

    string letterGrade; //declares a character variable to hold the letter grade

    //Letter grades are assigned based off of conditional statements and then returns the
    //variable
    if(grade <= 100 && grade >= 90){
        cout << "Your letter Grade is a A";
        letterGrade = "A";
    }
    else if(grade <= 89 && grade >= 80){
        cout << "Your letter grade is a B";
        letterGrade = "B";
    }
    else if (grade <= 79 && grade >= 70){
        cout << "Your letter grade is a C";
        letterGrade = "C";
    }
    else if (grade <= 69 && grade >= 60){
        cout << "Your letter grade is a D";
        letterGrade = "D";
    }
    else{
        cout << "Your letter grade is an F";
        letterGrade = "F";
    }

    return letterGrade;

}//Letter Grade function delimiter

//Return the length of the longest student name
int getLongestNameLength(const vector<Student> &students) {

    int maxLength = 0;
    for(int i = 0; i < students.size(); i++){

        int length = students[i].fName.length() +
                students[i].lName.length() + 1;

        if(length > maxLength){
            maxLength = length;
        }//Conditional delimiter

    }//Loop delimiter
    return maxLength;

}//LongestName function delimiter

//swap a & b
void swap(Student &a, Student &b) {

    Student temp = a;
    a = b;
    b = temp;

}

void bubbleSort(vector<Student> &students, bool (*doSwapTest)(Student &, Student &)){

    //Boolean flag variable
    bool didSwap = false;

    for(int i = students.size() - 1; i > 0; i--){
        didSwap = false;
        for(int j = 0; j < i; j++){

            if ((*doSwapTest)(students[j], students[j+1])){

                swap(students[j], students[j+1]);
                didSwap = false;

            }//Conditional Delimiter

        }//Inner loop delimiter
        if (!didSwap) break;

    }//Outer loop delimiter

}//Bubble Sort function delimiter

//Compare averages of Student grades
bool doAvgSwapTest(Student &first, Student &second) {
    return first.average < second.average;
}

//Compare maximums of Student grades
bool doMaxSwapTest(Student &first, Student &second) {
    return first.max < second.max;
}

//Compare minimums of Student Grades
bool doMinSwapTest(Student &first, Student &second) {
    return first.min < second.min;
}
