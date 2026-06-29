//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Nathan Godinez
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================
// Course Class
// ============================
class Course {
public:
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// ============================
// Global Data Structure
// ============================
vector<Course> courses;

// ============================
// Helper: Find course index
// ============================
int findCourseIndex(const string& courseNumber) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i].courseNumber == courseNumber) {
            return i;
        }
    }
    return -1;
}

// ============================
// Load file into data structure
// ============================
void loadCourses(const string& filename) {
    courses.clear();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        Course course;

        // Course number
        getline(ss, token, ',');
        course.courseNumber = token;

        // Course name
        getline(ss, token, ',');
        course.courseName = token;

        // Prerequisites (optional)
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courses.push_back(course);
    }

    file.close();
    cout << "Courses successfully loaded!\n";
}

// ============================
// Sort courses alphanumerically
// ============================
void sortCourses() {
    sort(courses.begin(), courses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });
}

// ============================
// Print full course list
// ============================
void printCourseList() {
    if (courses.empty()) {
        cout << "No courses loaded. Please load file first.\n";
        return;
    }

    sortCourses();

    cout << "\n==============================\n";
    cout << "Course List (Alphanumeric)\n";
    cout << "==============================\n";

    for (const auto& course : courses) {
        cout << course.courseNumber << ": " << course.courseName << endl;
    }
}

// ============================
// Print course details
// ============================
void printCourseInfo(const string& courseNumber) {
    int index = findCourseIndex(courseNumber);

    if (index == -1) {
        cout << "Course not found.\n";
        return;
    }

    Course course = courses[index];

    cout << "\n==============================\n";
    cout << course.courseNumber << ": " << course.courseName << endl;
    cout << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None";
    }
    else {
        for (int i = 0; i < course.prerequisites.size(); i++) {
            string prereqNum = course.prerequisites[i];
            cout << prereqNum;

            int prereqIndex = findCourseIndex(prereqNum);
            if (prereqIndex != -1) {
                cout << " (" << courses[prereqIndex].courseName << ")";
            }

            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
    }

    cout << "\n==============================\n";
}

// ============================
// Menu
// ============================
void displayMenu() {
    cout << "\n====== ABCU Advising System ======\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course Information\n";
    cout << "9. Exit\n";
    cout << "Select an option: ";
}

// ============================
// Main
// ============================
int main() {
    int choice;
    string filename;

    cout << "Welcome to ABCU Advising Assistance Program\n";

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> filename;
            loadCourses(filename);
            break;

        case 2:
            printCourseList();
            break;

        case 3:
            cout << "Enter course number: ";
            cin >> filename; // reuse variable
            printCourseInfo(filename);
            break;

        case 9:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
