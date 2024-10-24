#include <iostream>  // including header files in c++  //
#include <fstream>   // including header files in c++  //
#include <vector>    // including header files in c++  //
#include <algorithm>  // including header files in c++  //
#include <sstream>  // including header files in c++  //

using namespace std;

class Course {
public:
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course(string number, string title, vector<string> prereqs) {
        courseNumber = number;
        courseTitle = title;
        prerequisites = prereqs;
    }
};

vector<Course> courseData;

// Function to load data from the file into the data structure
void loadDataStructure(string fileName) {
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        vector<string> prereqs;
        while (getline(ss, prereq, ',')) {
            prereqs.push_back(prereq);
        }

        Course newCourse(courseNumber, courseTitle, prereqs);
        courseData.push_back(newCourse);
    }

    cout << "Data loaded into the data structure successfully." << endl;
}

// Function to print an alphanumeric list of all the courses
void printCourseList() {
    sort(courseData.begin(), courseData.end(), [](const Course& a, const Course& b) {   // using sorting algorithm  //
        return a.courseNumber < b.courseNumber;
    });

    cout << "Alphanumeric List of Courses:" << endl;
    for (const Course& course : courseData) {
        cout << course.courseNumber << ": " << course.courseTitle << endl;
    }
}

// Function to print course information based on the course number
void printCourseInfo(string courseNumber) {
    auto it = find_if(courseData.begin(), courseData.end(), [&](const Course& course) {  // equate auto //
        return course.courseNumber == courseNumber;
    });

    if (it != courseData.end()) {
        cout << "Course Information for " << courseNumber << ":" << endl;
        cout << "Title: " << it->courseTitle << endl;
        cout << "Prerequisites: ";

        if (it->prerequisites.empty()) {
            cout << "None";
        } else {
            for (const string& prereq : it->prerequisites) {
                cout << prereq << " ";
            }
        }

        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    cout << "ABCU Advising Program" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter the file name containing the course data: ";
                string fileName;
                cin >> fileName;
                loadDataStructure(fileName);
                break;
            }
            case 2:
                printCourseList();
                break;
            case 3: {
                cout << "Enter the course number: ";
                string courseNumber;
                cin >> courseNumber;
                printCourseInfo(courseNumber);
                break;
            }
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
