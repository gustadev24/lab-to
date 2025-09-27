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
  Teacher("T001", "Emily", "Carter", 24),
  Teacher("T002", "Michael", "Johnson", 30),
  Teacher("T003", "Sarah", "Williams", 28),
  Teacher("T004", "David", "Brown", 35),
  Teacher("T005", "Laura", "Davis", 26)
};

inline std::vector<Course> COURSES = {
  Course("C001", TEACHER[0], "Mathematics", 4),
  Course("C002", TEACHER[1], "Physics", 3),
  Course("C003", TEACHER[2], "Chemistry", 4),
  Course("C004", TEACHER[3], "Biology", 3),
  Course("C005", TEACHER[4], "History", 2),
  Course("C006", TEACHER[0], "Algebra", 3),
  Course("C007", TEACHER[1], "Calculus", 4),
  Course("C008", TEACHER[2], "Statistics", 3),
  Course("C009", TEACHER[3], "Geology", 2),
  Course("C010", TEACHER[4], "Philosophy", 3),
};

inline std::vector<Assignment> ASSIGNMENTS = {
  Assignment("A001", "Math Homework 1", STUDENTS[0], COURSES[0]),
  Assignment("A002", "Physics Lab Report", STUDENTS[1], COURSES[1]),
  Assignment("A003", "Chemistry Project", STUDENTS[2], COURSES[2]),
  Assignment("A004", "Biology Essay", STUDENTS[3], COURSES[3]),
  Assignment("A005", "History Presentation", STUDENTS[4], COURSES[4]),
  Assignment("A006", "Algebra Quiz", STUDENTS[5], COURSES[5]),
  Assignment("A007", "Calculus Test", STUDENTS[6], COURSES[6]),
  Assignment("A008", "Statistics Assignment", STUDENTS[7], COURSES[7]),
  Assignment("A009", "Geology Field Report", STUDENTS[8], COURSES[8]),
  Assignment("A010", "Philosophy Paper", STUDENTS[9], COURSES[9])
};
