#include <iostream>
#include <vector>
#include <iomanip>  // for setprecision
using namespace std;

struct Course {
    string name;
    double grade;      // Grade points (e.g., 9.0 for A, 8.0 for B)
    double creditHours;
};

int main() {
    int numCourses;
    cout << "Enter number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);

    double totalCredits = 0.0, totalGradePoints = 0.0;

    for (int i = 0; i < numCourses; i++) {
        cout << "\nCourse " << i + 1 << " name: ";
        cin >> courses[i].name;
        cout << "Enter grade points for " << courses[i].name << " (e.g. 10 for A+, 9 for A): ";
        cin >> courses[i].grade;
        cout << "Enter credit hours for " << courses[i].name << ": ";
        cin >> courses[i].creditHours;

        totalCredits += courses[i].creditHours;
        totalGradePoints += (courses[i].grade * courses[i].creditHours);
    }

    double GPA = totalGradePoints / totalCredits; // Semester GPA

    // Display details
    cout << "\n--- Course Details ---\n";
    for (int i = 0; i < numCourses; i++) {
        cout << "Course: " << courses[i].name
             << " | Grade: " << courses[i].grade
             << " | Credit Hours: " << courses[i].creditHours << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nTotal Credits: " << totalCredits << endl;
    cout << "Semester GPA: " << GPA << endl;

    // For CGPA, you can assume multiple semesters if required
    char more;
    double prevCGPA, prevCredits;
    cout << "\nDo you have previous CGPA data? (y/n): ";
    cin >> more;
    if (more == 'y' || more == 'Y') {
        cout << "Enter previous CGPA: ";
        cin >> prevCGPA;
        cout << "Enter total previous credits: ";
        cin >> prevCredits;

        double CGPA = ((prevCGPA * prevCredits) + totalGradePoints) / (prevCredits + totalCredits);
        cout << "Overall CGPA: " << CGPA << endl;
    } else {
        cout << "Overall CGPA (this semester only): " << GPA << endl;
    }

    return 0;
}
