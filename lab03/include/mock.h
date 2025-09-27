#pragma once
#include <vector>
#include "Assignment.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"

// Function to create and return mock data vectors with dynamically allocated objects
std::vector<Student*> createMockStudents();
std::vector<Teacher*> createMockTeachers();
std::vector<Course*> createMockCourses(const std::vector<Teacher*>& teachers);
std::vector<Assignment*> createMockAssignments(const std::vector<Student*>& students, const std::vector<Course*>& courses);
