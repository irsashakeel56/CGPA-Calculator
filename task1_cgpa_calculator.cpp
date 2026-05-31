/*
 * CodeAlpha Internship — Task 1: CGPA Calculator
 * Author: Intern
 * Description: Calculates semester GPA and overall CGPA from course grades and credit hours.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

struct Course {
    string name;
    float  gradePoints;   // e.g. A=4.0, B=3.0 ...
    int    creditHours;
};

// Convert letter grade to grade points (4.0 scale)
float letterToPoints(const string& grade) {
    if (grade == "A+" || grade == "A")  return 4.0f;
    if (grade == "A-")                  return 3.7f;
    if (grade == "B+")                  return 3.3f;
    if (grade == "B")                   return 3.0f;
    if (grade == "B-")                  return 2.7f;
    if (grade == "C+")                  return 2.3f;
    if (grade == "C")                   return 2.0f;
    if (grade == "C-")                  return 1.7f;
    if (grade == "D+")                  return 1.3f;
    if (grade == "D")                   return 1.0f;
    if (grade == "F")                   return 0.0f;
    return -1.0f; // invalid
}

float calculateGPA(const vector<Course>& courses) {
    float totalPoints = 0;
    int   totalCredits = 0;
    for (const auto& c : courses) {
        totalPoints  += c.gradePoints * c.creditHours;
        totalCredits += c.creditHours;
    }
    return (totalCredits == 0) ? 0 : totalPoints / totalCredits;
}

int main() {
    cout << "========================================\n";
    cout << "       CodeAlpha — CGPA Calculator      \n";
    cout << "========================================\n\n";

    int numSemesters;
    cout << "Enter number of semesters: ";
    cin >> numSemesters;

    vector<float> semesterGPAs;
    vector<int>   semesterCredits;
    float overallPoints  = 0;
    int   overallCredits = 0;

    for (int s = 1; s <= numSemesters; s++) {
        cout << "\n--- Semester " << s << " ---\n";
        int numCourses;
        cout << "Number of courses: ";
        cin >> numCourses;
        cin.ignore();

        vector<Course> courses;
        for (int i = 1; i <= numCourses; i++) {
            Course c;
            cout << "  Course " << i << " name : ";
            getline(cin, c.name);
            cout << "  Credit hours   : ";
            cin >> c.creditHours;

            string grade;
            while (true) {
                cout << "  Grade (A/A-/B+/B/B-/C+/C/C-/D+/D/F): ";
                cin >> grade;
                c.gradePoints = letterToPoints(grade);
                if (c.gradePoints >= 0) break;
                cout << "  Invalid grade, please try again.\n";
            }
            cin.ignore();
            courses.push_back(c);
        }

        // Print semester table
        cout << "\n  Course                        Credits   Grade\n";
        cout << "  " << string(50, '-') << "\n";
        for (const auto& c : courses) {
            cout << "  " << left << setw(30) << c.name
                 << setw(9) << c.creditHours
                 << c.gradePoints << "\n";
        }

        float gpa = calculateGPA(courses);
        int   totalCr = 0;
        float totalPt = 0;
        for (const auto& c : courses) {
            totalCr      += c.creditHours;
            totalPt      += c.gradePoints * c.creditHours;
            overallPoints  += c.gradePoints * c.creditHours;
            overallCredits += c.creditHours;
        }
        semesterGPAs.push_back(gpa);
        semesterCredits.push_back(totalCr);

        cout << "  " << string(50, '-') << "\n";
        cout << "  Semester GPA: " << fixed << setprecision(2) << gpa << "\n";
    }

    // Overall CGPA
    float cgpa = (overallCredits == 0) ? 0 : overallPoints / overallCredits;

    cout << "\n========================================\n";
    cout << "         Semester GPA Summary\n";
    cout << "========================================\n";
    for (int i = 0; i < (int)semesterGPAs.size(); i++) {
        cout << "  Semester " << i + 1 << ":  GPA = "
             << fixed << setprecision(2) << semesterGPAs[i]
             << "  (" << semesterCredits[i] << " credits)\n";
    }
    cout << "----------------------------------------\n";
    cout << "  Overall CGPA : " << fixed << setprecision(2) << cgpa << "\n";
    cout << "  Total Credits: " << overallCredits << "\n";
    cout << "========================================\n";

    return 0;
}
