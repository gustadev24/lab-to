#include "mock.h"
#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Assignment.h"
#include "Grade.h"

std::vector<Student*> createMockStudents() {
    std::vector<Student*> students;
    students.push_back(new Student("S001", &Grade::FIFTH, "Alice", "Johnson"));
    students.push_back(new Student("S002", &Grade::SIXTH, "Bob", "Smith"));
    students.push_back(new Student("S003", &Grade::FIRST, "Charlie", "Brown"));
    students.push_back(new Student("S004", &Grade::SECOND, "Diana", "Prince"));
    students.push_back(new Student("S005", &Grade::THIRD, "Ethan", "Hunt"));
    students.push_back(new Student("S006", &Grade::FOURTH, "Fiona", "Gallagher"));
    students.push_back(new Student("S007", &Grade::FIFTH, "George", "Miller"));
    students.push_back(new Student("S008", &Grade::SIXTH, "Hannah", "Montana"));
    students.push_back(new Student("S009", &Grade::FIRST, "Ian", "Sommerhalder"));
    students.push_back(new Student("S010", &Grade::SECOND, "Jenna", "Marbles"));
    return students;
}

std::vector<Teacher*> createMockTeachers() {
    std::vector<Teacher*> teachers;
    teachers.push_back(new Teacher("T001", "Emily", "Carter", 24, &Grade::FIRST));
    teachers.push_back(new Teacher("T002", "Michael", "Johnson", 30, &Grade::SECOND));
    teachers.push_back(new Teacher("T003", "Sarah", "Williams", 28, &Grade::THIRD));
    teachers.push_back(new Teacher("T004", "David", "Brown", 35, &Grade::FOURTH));
    teachers.push_back(new Teacher("T005", "Laura", "Davis", 32, &Grade::FIFTH));
    teachers.push_back(new Teacher("T006", "James", "Miller", 29, &Grade::SIXTH));
    teachers.push_back(new Teacher("T007", "Olivia", "Wilson", 27));
    teachers.push_back(new Teacher("T008", "Daniel", "Moore", 31));
    teachers.push_back(new Teacher("T009", "Sophia", "Taylor", 26));
    teachers.push_back(new Teacher("T010", "Matthew", "Anderson", 33));
    return teachers;
}

std::vector<Course*> createMockCourses(const std::vector<Teacher*>& teachers) {
    std::vector<Course*> courses;
    courses.push_back(new Course("C001", teachers[0], "Mathematics", 4));
    courses.push_back(new Course("C002", teachers[1], "Physics", 3));
    courses.push_back(new Course("C003", teachers[2], "Chemistry", 4));
    courses.push_back(new Course("C004", teachers[3], "Biology", 3));
    courses.push_back(new Course("C005", teachers[4], "History", 2));
    courses.push_back(new Course("C006", teachers[5], "Geography", 2));
    courses.push_back(new Course("C007", teachers[6], "English Literature", 3));
    courses.push_back(new Course("C008", teachers[7], "Computer Science", 4));
    courses.push_back(new Course("C009", teachers[8], "Art", 2));
    courses.push_back(new Course("C010", teachers[9], "Physical Education", 1));

    // Demonstrate that teachers can teach multiple courses
    courses.push_back(new Course("C011", teachers[0], "Advanced Mathematics", 4)); // Emily teaches 2 courses
    courses.push_back(new Course("C012", teachers[1], "Advanced Physics", 3));     // Michael teaches 2 courses
    courses.push_back(new Course("C013", teachers[7], "Programming Fundamentals", 3)); // Daniel teaches 2 courses
    courses.push_back(new Course("C014", teachers[6], "Creative Writing", 2));     // Olivia teaches 2 courses

    return courses;
}

std::vector<Assignment*> createMockAssignments(const std::vector<Student*>& students, const std::vector<Course*>& courses) {
    std::vector<Assignment*> assignments;

    // Create assignments - some will be presented, some pending
    Assignment* a1 = new Assignment("A001", "Algebra Homework", students[0], courses[0]);
    a1->present(); // Mark as presented
    assignments.push_back(a1);

    Assignment* a2 = new Assignment("A002", "Physics Lab Report", students[1], courses[1]);
    // Leave as pending (not presented)
    assignments.push_back(a2);

    Assignment* a3 = new Assignment("A003", "Chemistry Project", students[2], courses[2]);
    a3->present(); // Mark as presented
    assignments.push_back(a3);

    Assignment* a4 = new Assignment("A004", "Biology Presentation", students[3], courses[3]);
    // Leave as pending
    assignments.push_back(a4);

    Assignment* a5 = new Assignment("A005", "History Essay", students[4], courses[4]);
    a5->present(); // Mark as presented
    assignments.push_back(a5);

    Assignment* a6 = new Assignment("A006", "Geography Map Analysis", students[5], courses[5]);
    // Leave as pending
    assignments.push_back(a6);

    Assignment* a7 = new Assignment("A007", "English Literature Review", students[6], courses[6]);
    a7->present(); // Mark as presented
    assignments.push_back(a7);

    Assignment* a8 = new Assignment("A008", "Computer Science Coding Assignment", students[7], courses[7]);
    // Leave as pending
    assignments.push_back(a8);

    Assignment* a9 = new Assignment("A009", "Art Portfolio", students[8], courses[8]);
    a9->present(); // Mark as presented
    assignments.push_back(a9);

    Assignment* a10 = new Assignment("A010", "Physical Education Fitness Plan", students[9], courses[9]);
    // Leave as pending
    assignments.push_back(a10);

    // Add some additional assignments to demonstrate multiple assignments per student
    Assignment* a11 = new Assignment("A011", "Advanced Algebra", students[0], courses[10]); // Student S001 has 2 assignments
    // Leave as pending
    assignments.push_back(a11);

    Assignment* a12 = new Assignment("A012", "Physics Experiment", students[1], courses[11]); // Student S002 has 2 assignments
    a12->present(); // Mark as presented
    assignments.push_back(a12);

    Assignment* a13 = new Assignment("A013", "Programming Project", students[7], courses[12]); // Student S008 has 2 assignments
    a13->present(); // Mark as presented
    assignments.push_back(a13);

    return assignments;
}
