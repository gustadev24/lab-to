#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "Grade.h"
#include "School.h"
#include "mock.h"

std::vector<std::string> options = {
  "Register Student",
  "See all students",
  "Register Teacher",
  "See all teachers",
  "Search assignments per student",
  "Search students per teacher",
};

Grade stringToGrade(const std::string& gradeStr) {
  if (gradeStr == "1" || gradeStr == "FIRST") return Grade::FIRST;
  if (gradeStr == "2" || gradeStr == "SECOND") return Grade::SECOND;
  if (gradeStr == "3" || gradeStr == "THIRD") return Grade::THIRD;
  if (gradeStr == "4" || gradeStr == "FOURTH") return Grade::FOURTH;
  if (gradeStr == "5" || gradeStr == "FIFTH") return Grade::FIFTH;
  if (gradeStr == "6" || gradeStr == "SIXTH") return Grade::SIXTH;
  return Grade::FIRST; // default
}  // Helper function to convert string to Grade enum


// Clear input buffer
void clearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Get string input from user
std::string getStringInput(const std::string& prompt) {
  std::string input;
  std::cout << prompt;
  std::getline(std::cin, input);
  return input;
}

// Register a new student
void registerStudent(School& school) {
  std::cout << "\n--- Register New Student ---" << std::endl;

  std::string id = getStringInput("Enter student ID: ");
  std::string names = getStringInput("Enter student names: ");
  std::string surnames = getStringInput("Enter student surnames: ");

  std::cout << "Available grades: 1(First), 2(Second), 3(Third), 4(Fourth), 5(Fifth), 6(Sixth)" << std::endl;
  std::string gradeInput = getStringInput("Enter student grade (1-6): ");

  Grade grade = stringToGrade(gradeInput);

  Student newStudent(id, grade, names, surnames);
  school.addStudent(newStudent);

  std::cout << "Student registered successfully!" << std::endl;
  std::cout << "Student info: " << newStudent.toString() << std::endl;
}

// Display all students
void seeAllStudents(School& school) {
  std::cout << "\n--- All Students ---" << std::endl;
  auto students = school.getStudents();

  if (students.empty()) {
    std::cout << "No students registered." << std::endl;
    return;
  }

  for (size_t i = 0; i < students.size(); i++){
    std::cout << (i + 1) << ". " << students.at(i).toString() << std::endl;
  }
}

// Register a new teacher
void registerTeacher(School& school) {
  std::cout << "\n--- Register New Teacher ---" << std::endl;

  std::string id = getStringInput("Enter teacher ID: ");
  std::string names = getStringInput("Enter teacher names: ");
  std::string surnames = getStringInput("Enter teacher surnames: ");

  int age;
  std::cout << "Enter teacher age: ";
  while (!(std::cin >> age) || age < 18 || age > 100) {
    std::cout << "Please enter a valid age (18-100): ";
    clearInputBuffer();
  }
  clearInputBuffer(); // Clear the newline after reading age

  std::string responsibleChoice = getStringInput("Is this teacher responsible for a specific grade? (y/n): ");

  Teacher newTeacher(id, names, surnames, age);

  if (responsibleChoice == "y" || responsibleChoice == "Y" || responsibleChoice == "yes") {
    std::cout << "Available grades: 1(First), 2(Second), 3(Third), 4(Fourth), 5(Fifth), 6(Sixth)" << std::endl;
    std::string gradeInput = getStringInput("Enter responsible grade (1-6): ");
    Grade responsibleGrade = stringToGrade(gradeInput);
    newTeacher = Teacher(id, names, surnames, age, responsibleGrade);
  }

  school.addTeacher(newTeacher);

  std::cout << "Teacher registered successfully!" << std::endl;
  std::cout << "Teacher info: " << newTeacher.toString() << std::endl;
}

// Display all teachers
void seeAllTeachers(School& school) {
  std::cout << "\n--- All Teachers ---" << std::endl;
  auto teachers = school.getTeachers();

  if (teachers.empty()) {
    std::cout << "No teachers registered." << std::endl;
    return;
  }

  for (size_t i = 0; i < teachers.size(); i++) {
    std::cout << (i + 1) << ". " << teachers[i].toString() << std::endl;
  }
}

// Search assignments per student
void searchAssignmentsPerStudent(School& school) {
  std::cout << "\n--- Search Assignments per Student ---" << std::endl;

  std::string studentId = getStringInput("Enter student ID: ");

  auto assignments = school.getPresentedAssignmentsByStudentId(studentId);

  if (assignments.empty()) {
    std::cout << "No assignments found for student ID: " << studentId << std::endl;
    return;
  }

  std::cout << "Assignments for student " << studentId << ":" << std::endl;
  for (size_t i = 0; i < assignments.size(); i++) {
    auto& assignment = assignments[i];
    std::cout << (i + 1) << ". Assignment: " << assignment.getName()
    << " (ID: " << assignment.getId() << ")" << std::endl;
    std::cout << "   Course: " << assignment.getCourse().getName() << std::endl;
    std::cout << "   Presented: " << (assignment.isPresented() ? "Yes" : "No") << std::endl;
    if (assignment.getPresentationDate()) {
      std::cout << "   Presentation Date: " << assignment.getPresentationDate().value() << std::endl;
    }
  }
}

// Search students per teacher
void searchStudentsPerTeacher(School& school) {
  std::cout << "\n--- Search Students per Teacher ---" << std::endl;

  std::string teacherId = getStringInput("Enter teacher ID: ");

  auto students = school.getStudentsByTeacherId(teacherId);

  if (students.empty()) {
    std::cout << "No students found for teacher ID: " << teacherId << std::endl;
    return;
  }

  std::cout << "Students taught by teacher " << teacherId << ":" << std::endl;
  for (size_t i = 0; i < students.size(); i++) {
    std::cout << (i + 1) << ". " << students[i].toString() << std::endl;
  }
}

int readOption() {
  std::cout << "\nChoose an option:" << std::endl;
  for (size_t i = 0; i < options.size(); i++) {
    std::cout << i + 1 << ". " << options[i] << std::endl;
  }
  std::cout << "0. Exit" << std::endl;

  int option;
  std::cout << "Enter your choice: ";
  std::cin >> option;

  if (std::cin.fail() || option < 0 || option > static_cast<int>(options.size())) {
    clearInputBuffer();
    return -1;
  }

  clearInputBuffer(); // Clear the newline after reading option
  return option;
}

int main() {
  std::cout << "Welcome to Classroom Management System" << std::endl;
  School school(STUDENTS, TEACHER, COURSES, ASSIGNMENTS);

  bool running = true;
  do {
    int option = readOption();
    if (option == -1) {
      std::cout << "Invalid option. Please try again." << std::endl;
      continue;
    }

    switch (option) {
      case 1:
      registerStudent(school);
      break;
      case 2:
      seeAllStudents(school);
      break;
      case 3:
      registerTeacher(school);
      break;
      case 4:
      seeAllTeachers(school);
      break;
      case 5:
      searchAssignmentsPerStudent(school);
      break;
      case 6:
      searchStudentsPerTeacher(school);
      break;
      case 0:
      std::cout << "Exiting classroom management system..." << std::endl;
      running = false;
      break;
      default:
      std::cout << "Invalid option. Please try again." << std::endl;
      break;
    }
  } while (running);

  return 0;
}
