#pragma once
#include <vector>
#include "Assignment.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"

inline std::vector<Student> STUDENTS = {
    Student("S001", Grade::FIFTH, "Alice", "Johnson"),
    Student("S002", Grade::SIXTH, "Bob", "Smith"),
    Student("S003", Grade::FIRST, "Charlie", "Brown"),
    Student("S004", Grade::SECOND, "Diana", "Prince"),
    Student("S005", Grade::THIRD, "Ethan", "Hunt"),
    Student("S006", Grade::FOURTH, "Fiona", "Gallagher"),
    Student("S007", Grade::FIFTH, "George", "Miller"),
    Student("S008", Grade::SIXTH, "Hannah", "Montana"),
    Student("S009", Grade::FIRST, "Ian", "Sommerhalder"),
    Student("S010", Grade::SECOND, "Jenna", "Marbles")
};

inline std::vector<Teacher> TEACHER = {
  Teacher("T001", "Emily", "Carter", 24, Grade::FIRST),
  Teacher("T002", "Michael", "Johnson", 30, Grade::SECOND),
  Teacher("T003", "Sarah", "Williams", 28, Grade::THIRD),
  Teacher("T004", "David", "Brown", 35, Grade::FOURTH),
  Teacher("T005", "Laura", "Davis", 32, Grade::FIFTH),
  Teacher("T006", "James", "Miller", 29, Grade::SIXTH),
  Teacher("T007", "Olivia", "Wilson", 27),
  Teacher("T008", "Daniel", "Moore", 31),
  Teacher("T009", "Sophia", "Taylor", 26),
  Teacher("T010", "Matthew", "Anderson", 33)
};

inline std::vector<Course> COURSES = {
  Course("C001", TEACHER[0], "Mathematics", 4),
  Course("C002", TEACHER[1], "Physics", 3),
  Course("C003", TEACHER[2], "Chemistry", 4),
  Course("C004", TEACHER[3], "Biology", 3),
  Course("C005", TEACHER[4], "History", 2),
  Course("C006", TEACHER[5], "Geography", 2),
  Course("C007", TEACHER[6], "English Literature", 3),
  Course("C008", TEACHER[7], "Computer Science", 4),
  Course("C009", TEACHER[8], "Art", 2),
  Course("C010", TEACHER[9], "Physical Education", 1)
};

inline std::vector<Assignment> ASSIGNMENTS = {
  Assignment("A001", "Algebra Homework", STUDENTS[0], COURSES[0]),
  Assignment("A002", "Physics Lab Report", STUDENTS[1], COURSES[1]),
  Assignment("A003", "Chemistry Project", STUDENTS[2], COURSES[2]),
  Assignment("A004", "Biology Presentation", STUDENTS[3], COURSES[3]),
  Assignment("A005", "History Essay", STUDENTS[4], COURSES[4]),
  Assignment("A006", "Geography Map Analysis", STUDENTS[5], COURSES[5]),
  Assignment("A007", "English Literature Review", STUDENTS[6], COURSES[6]),
  Assignment("A008", "Computer Science Coding Assignment", STUDENTS[7], COURSES[7]),
  Assignment("A009", "Art Portfolio", STUDENTS[8], COURSES[8]),
  Assignment("A010", "Physical Education Fitness Plan", STUDENTS[9], COURSES[9])
};
