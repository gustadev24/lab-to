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
  "Search all assignments per student (presented/pending)",
  "Search students per teacher",
  "Assign teacher to new course",
  "See all courses with teachers",
  "Mark assignment as presented",
  "Show assignment delivery statistics",
  "Show specific teacher statistics",
  "Search student by ID",
  "Search teachers by name",
  "Search students by course",
  "Comprehensive search menu",
};

// Helper function to convert string to Grade pointer
const Grade* stringToGrade(const std::string& gradeStr) {
  if (gradeStr == "1" || gradeStr == "FIRST") return &Grade::FIRST;
  if (gradeStr == "2" || gradeStr == "SECOND") return &Grade::SECOND;
  if (gradeStr == "3" || gradeStr == "THIRD") return &Grade::THIRD;
  if (gradeStr == "4" || gradeStr == "FOURTH") return &Grade::FOURTH;
  if (gradeStr == "5" || gradeStr == "FIFTH") return &Grade::FIFTH;
  if (gradeStr == "6" || gradeStr == "SIXTH") return &Grade::SIXTH;
  return &Grade::FIRST; // default
}

// Helper function to convert Grade pointer to string
std::string gradeToString(const Grade* grade) {
  return grade->getName();
}

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

  const Grade* grade = stringToGrade(gradeInput);

  Student* newStudent = new Student(id, grade, names, surnames);
  school.addStudent(newStudent);

  std::cout << "Student registered successfully!" << std::endl;
  std::cout << "Student info: " << newStudent->toString() << std::endl;
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
    std::cout << (i + 1) << ". " << students.at(i)->toString() << std::endl;
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

  Teacher* newTeacher = new Teacher(id, names, surnames, age);

  if (responsibleChoice == "y" || responsibleChoice == "Y" || responsibleChoice == "yes") {
    std::cout << "Available grades: 1(First), 2(Second), 3(Third), 4(Fourth), 5(Fifth), 6(Sixth)" << std::endl;
    std::string gradeInput = getStringInput("Enter responsible grade (1-6): ");
    const Grade* responsibleGrade = stringToGrade(gradeInput);
    delete newTeacher; // Delete the old one
    newTeacher = new Teacher(id, names, surnames, age, responsibleGrade);
  }

  school.addTeacher(newTeacher);

  std::cout << "Teacher registered successfully!" << std::endl;
  std::cout << "Teacher info: " << newTeacher->toString() << std::endl;
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
    std::cout << (i + 1) << ". " << teachers[i]->toString() << std::endl;
  }
}

// Search assignments per student (presented and pending)
void searchAssignmentsPerStudent(School& school) {
  std::cout << "\n--- Search All Assignments per Student (Presented and Pending) ---" << std::endl;

  std::string studentId = getStringInput("Enter student ID: ");

  auto allAssignments = school.getAllAssignmentsByStudentId(studentId);

  if (allAssignments.empty()) {
    std::cout << "No assignments found for student ID: " << studentId << std::endl;
    return;
  }

  // Separate assignments into presented and pending
  std::vector<Assignment*> presentedAssignments;
  std::vector<Assignment*> pendingAssignments;

  for (auto assignment : allAssignments) {
    if (assignment->isPresented()) {
      presentedAssignments.push_back(assignment);
    } else {
      pendingAssignments.push_back(assignment);
    }
  }

  std::cout << "\n=== ASSIGNMENTS SUMMARY FOR STUDENT " << studentId << " ===" << std::endl;
  std::cout << "Total assignments: " << allAssignments.size() << std::endl;
  std::cout << "Presented (delivered): " << presentedAssignments.size() << std::endl;
  std::cout << "Pending: " << pendingAssignments.size() << std::endl;

  // Show presented assignments
  if (!presentedAssignments.empty()) {
    std::cout << "\n✓ PRESENTED ASSIGNMENTS:" << std::endl;
    for (size_t i = 0; i < presentedAssignments.size(); i++) {
      auto& assignment = presentedAssignments[i];
      std::cout << "  " << (i + 1) << ". Assignment: " << assignment->getName()
                << " (ID: " << assignment->getId() << ")" << std::endl;
      std::cout << "     Course: " << assignment->getCourse()->getName() << std::endl;
      std::cout << "     Status: ✓ DELIVERED" << std::endl;
      if (assignment->getPresentationDate()) {
        std::cout << "     Presentation Date: " << assignment->getPresentationDate().value() << std::endl;
      }
      std::cout << "     ---" << std::endl;
    }
  }

  // Show pending assignments
  if (!pendingAssignments.empty()) {
    std::cout << "\n⏳ PENDING ASSIGNMENTS:" << std::endl;
    for (size_t i = 0; i < pendingAssignments.size(); i++) {
      auto& assignment = pendingAssignments[i];
      std::cout << "  " << (i + 1) << ". Assignment: " << assignment->getName()
                << " (ID: " << assignment->getId() << ")" << std::endl;
      std::cout << "     Course: " << assignment->getCourse()->getName() << std::endl;
      std::cout << "     Status: ⏳ PENDING" << std::endl;
      std::cout << "     ---" << std::endl;
    }
  }

  // Show completion percentage
  if (!allAssignments.empty()) {
    double completionRate = (double)presentedAssignments.size() / allAssignments.size() * 100.0;
    std::cout << "\n📊 COMPLETION RATE: " << completionRate << "% ("
              << presentedAssignments.size() << "/" << allAssignments.size() << " assignments completed)" << std::endl;
  }

  std::cout << "=======================================" << std::endl;
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
    std::cout << (i + 1) << ". " << students[i]->toString() << std::endl;
  }
}

// Assign teacher to new course
void assignTeacherToNewCourse(School& school) {
  std::cout << "\n--- Assign Teacher to New Course ---" << std::endl;

  // Show available teachers
  std::cout << "Available teachers:" << std::endl;
  const auto& teachers = school.getTeachers();
  for (size_t i = 0; i < teachers.size(); i++) {
    std::cout << (i + 1) << ". " << teachers[i]->getNames() << " " << teachers[i]->getSurnames()
              << " (ID: " << teachers[i]->getId() << ")" << std::endl;
  }

  std::string teacherId = getStringInput("\nEnter teacher ID: ");

  // Verify teacher exists
  Teacher* selectedTeacher = nullptr;
  for (auto teacher : teachers) {
    if (teacher->getId() == teacherId) {
      selectedTeacher = teacher;
      break;
    }
  }

  if (selectedTeacher == nullptr) {
    std::cout << "Teacher with ID " << teacherId << " not found." << std::endl;
    return;
  }

  // Show current courses for this teacher
  auto currentCourses = school.getCoursesByTeacherId(teacherId);
  std::cout << "\nTeacher " << selectedTeacher->getNames() << " " << selectedTeacher->getSurnames()
            << " currently teaches " << currentCourses.size() << " course(s):" << std::endl;
  for (size_t i = 0; i < currentCourses.size(); i++) {
    std::cout << "  " << (i + 1) << ". " << currentCourses[i]->getName()
              << " (" << currentCourses[i]->getId() << ")" << std::endl;
  }

  // Get new course details
  std::string courseId = getStringInput("\nEnter new course ID: ");
  std::string courseName = getStringInput("Enter course name: ");

  int credits;
  std::cout << "Enter course credits: ";
  while (!(std::cin >> credits) || credits < 1 || credits > 10) {
    std::cout << "Please enter valid credits (1-10): ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // Create and add new course
  Course* newCourse = new Course(courseId, selectedTeacher, courseName, credits);
  school.addCourse(newCourse);

  std::cout << "\n✓ Course created successfully!" << std::endl;
  std::cout << "Course info: " << newCourse->toString() << std::endl;

  // Show updated courses for this teacher
  auto updatedCourses = school.getCoursesByTeacherId(teacherId);
  std::cout << "\nTeacher " << selectedTeacher->getNames() << " " << selectedTeacher->getSurnames()
            << " now teaches " << updatedCourses.size() << " course(s):" << std::endl;
  for (size_t i = 0; i < updatedCourses.size(); i++) {
    std::cout << "  " << (i + 1) << ". " << updatedCourses[i]->getName()
              << " (" << updatedCourses[i]->getId() << ")" << std::endl;
  }

  if (updatedCourses.size() > 1) {
    std::cout << "\n✓ VERIFICATION: This demonstrates that teacher " << teacherId
              << " can teach multiple courses!" << std::endl;
  }
}

// See all courses with their teachers
void seeAllCoursesWithTeachers(School& school) {
  std::cout << "\n--- All Courses with Teachers ---" << std::endl;
  const auto& courses = school.getCourses();

  if (courses.empty()) {
    std::cout << "No courses registered." << std::endl;
    return;
  }

  std::cout << "Total courses: " << courses.size() << std::endl;
  std::cout << "=======================================" << std::endl;

  for (size_t i = 0; i < courses.size(); i++) {
    std::cout << (i + 1) << ". Course: " << courses[i]->getName()
              << " (ID: " << courses[i]->getId() << ")" << std::endl;
    std::cout << "   Credits: " << courses[i]->getCredits() << std::endl;
    std::cout << "   Teacher: " << courses[i]->getTeacher()->getNames()
              << " " << courses[i]->getTeacher()->getSurnames()
              << " (ID: " << courses[i]->getTeacher()->getId() << ")" << std::endl;
    std::cout << "   ---" << std::endl;
  }

  // Group courses by teacher to show which teachers teach multiple courses
  std::cout << "\n--- Teachers and Their Courses ---" << std::endl;
  const auto& teachers = school.getTeachers();

  for (auto teacher : teachers) {
    auto teacherCourses = school.getCoursesByTeacherId(teacher->getId());
    if (!teacherCourses.empty()) {
      std::cout << "• " << teacher->getNames() << " " << teacher->getSurnames()
                << " (ID: " << teacher->getId() << ") teaches "
                << teacherCourses.size() << " course(s):" << std::endl;
      for (auto course : teacherCourses) {
        std::cout << "  - " << course->getName() << " (" << course->getId() << ")" << std::endl;
      }
      if (teacherCourses.size() > 1) {
        std::cout << "    ✓ This teacher teaches multiple courses!" << std::endl;
      }
      std::cout << std::endl;
    }
  }
}

// Mark assignment as presented
void markAssignmentAsPresented(School& school) {
  std::cout << "\n--- Mark Assignment as Presented ---" << std::endl;

  std::string studentId = getStringInput("Enter student ID: ");

  auto allAssignments = school.getAllAssignmentsByStudentId(studentId);

  if (allAssignments.empty()) {
    std::cout << "No assignments found for student ID: " << studentId << std::endl;
    return;
  }

  // Find pending assignments
  std::vector<Assignment*> pendingAssignments;
  for (auto assignment : allAssignments) {
    if (!assignment->isPresented()) {
      pendingAssignments.push_back(assignment);
    }
  }

  if (pendingAssignments.empty()) {
    std::cout << "Student " << studentId << " has no pending assignments. All assignments are already presented!" << std::endl;
    return;
  }

  std::cout << "\nPending assignments for student " << studentId << ":" << std::endl;
  for (size_t i = 0; i < pendingAssignments.size(); i++) {
    std::cout << (i + 1) << ". " << pendingAssignments[i]->getName()
              << " (ID: " << pendingAssignments[i]->getId() << ")"
              << " - Course: " << pendingAssignments[i]->getCourse()->getName() << std::endl;
  }

  std::string assignmentId = getStringInput("\nEnter assignment ID to mark as presented: ");

  // Find and mark the assignment as presented
  Assignment* selectedAssignment = nullptr;
  for (auto assignment : pendingAssignments) {
    if (assignment->getId() == assignmentId) {
      selectedAssignment = assignment;
      break;
    }
  }

  if (selectedAssignment == nullptr) {
    std::cout << "Assignment with ID " << assignmentId << " not found or already presented." << std::endl;
    return;
  }

  selectedAssignment->present();
  std::cout << "\n✓ Assignment '" << selectedAssignment->getName()
            << "' has been marked as presented!" << std::endl;
  std::cout << "Presentation Date: " << selectedAssignment->getPresentationDate().value() << std::endl;

  // Show updated summary
  auto updatedAssignments = school.getAllAssignmentsByStudentId(studentId);
  int presentedCount = 0;
  for (auto assignment : updatedAssignments) {
    if (assignment->isPresented()) {
      presentedCount++;
    }
  }

  double completionRate = (double)presentedCount / updatedAssignments.size() * 100.0;
  std::cout << "\nUpdated completion rate for student " << studentId << ": "
            << completionRate << "% (" << presentedCount << "/"
            << updatedAssignments.size() << " assignments completed)" << std::endl;
}

// Show assignment delivery statistics
void showAssignmentDeliveryStatistics(School& school) {
  school.showAssignmentDeliveryStatistics();
}

// Show specific teacher statistics
void showSpecificTeacherStatistics(School& school) {
  std::cout << "\n--- Show Specific Teacher Statistics ---" << std::endl;

  std::string teacherId = getStringInput("Enter teacher ID: ");
  school.showTeacherStatistics(teacherId);
}

// Search student by ID
void searchStudentById(School& school) {
  std::cout << "\n--- Search Student by ID ---" << std::endl;

  std::string studentId = getStringInput("Enter student ID: ");

  Student* student = school.searchStudentById(studentId);

  if (student == nullptr) {
    std::cout << "Student with ID " << studentId << " not found." << std::endl;
    return;
  }

  std::cout << "\n✓ Student found:" << std::endl;
  std::cout << student->toString() << std::endl;

  // Show additional information
  auto assignments = school.getAllAssignmentsByStudentId(studentId);
  int deliveredCount = 0;
  for (auto assignment : assignments) {
    if (assignment->isPresented()) {
      deliveredCount++;
    }
  }

  std::cout << "Total assignments: " << assignments.size() << std::endl;
  std::cout << "Delivered assignments: " << deliveredCount << std::endl;
  if (!assignments.empty()) {
    double percentage = (double)deliveredCount / assignments.size() * 100.0;
    std::cout << "Delivery percentage: " << percentage << "%" << std::endl;
  }
}

// Search teachers by name
void searchTeachersByName(School& school) {
  std::cout << "\n--- Search Teachers by Name ---" << std::endl;

  std::string teacherName = getStringInput("Enter teacher name (partial name allowed): ");

  auto teachers = school.searchTeachersByName(teacherName);

  if (teachers.empty()) {
    std::cout << "No teachers found with name containing: " << teacherName << std::endl;
    return;
  }

  std::cout << "\n✓ Found " << teachers.size() << " teacher(s):" << std::endl;
  for (size_t i = 0; i < teachers.size(); i++) {
    std::cout << (i + 1) << ". " << teachers[i]->toString() << std::endl;

    // Show courses taught by this teacher
    auto courses = school.getCoursesByTeacherId(teachers[i]->getId());
    if (!courses.empty()) {
      std::cout << "   Courses taught: ";
      for (size_t j = 0; j < courses.size(); j++) {
        if (j > 0) std::cout << ", ";
        std::cout << courses[j]->getName();
      }
      std::cout << std::endl;
    }

    // Show students under responsibility
    auto students = school.getStudentsByTeacherId(teachers[i]->getId());
    std::cout << "   Students under responsibility: " << students.size() << std::endl;
  }
}

// Search students by course
void searchStudentsByCourse(School& school) {
  std::cout << "\n--- Search Students by Course ---" << std::endl;

  std::string courseId = getStringInput("Enter course ID: ");

  Course* course = school.searchCourseById(courseId);
  if (course == nullptr) {
    std::cout << "Course with ID " << courseId << " not found." << std::endl;
    return;
  }

  auto students = school.searchStudentsByCourse(courseId);

  if (students.empty()) {
    std::cout << "No students found for course: " << course->getName() << std::endl;
    return;
  }

  std::cout << "\n✓ Course: " << course->getName() << " (" << courseId << ")" << std::endl;
  std::cout << "Teacher: " << course->getTeacher()->getNames() << " "
            << course->getTeacher()->getSurnames() << std::endl;
  std::cout << "Students enrolled (" << students.size() << "):" << std::endl;

  for (size_t i = 0; i < students.size(); i++) {
    std::cout << (i + 1) << ". " << students[i]->toString() << std::endl;

    // Show assignments for this student in this course
    auto allAssignments = school.getAllAssignmentsByStudentId(students[i]->getId());
    int courseAssignments = 0;
    int deliveredCourseAssignments = 0;

    for (auto assignment : allAssignments) {
      if (assignment->getCourse()->getId() == courseId) {
        courseAssignments++;
        if (assignment->isPresented()) {
          deliveredCourseAssignments++;
        }
      }
    }

    std::cout << "   Assignments in this course: " << deliveredCourseAssignments
              << "/" << courseAssignments;
    if (courseAssignments > 0) {
      double percentage = (double)deliveredCourseAssignments / courseAssignments * 100.0;
      std::cout << " (" << percentage << "%)";
    }
    std::cout << std::endl;
  }
}

// Helper function to show available search options
void showAvailableSearchOptions(School& school) {
  std::cout << "\n--- Available Search Options ---" << std::endl;

  // Show available student IDs
  const auto& students = school.getStudents();
  std::cout << "Available Student IDs: ";
  for (size_t i = 0; i < students.size() && i < 5; i++) {
    if (i > 0) std::cout << ", ";
    std::cout << students[i]->getId();
  }
  if (students.size() > 5) {
    std::cout << " ... (and " << (students.size() - 5) << " more)";
  }
  std::cout << std::endl;

  // Show available teacher names
  const auto& teachers = school.getTeachers();
  std::cout << "Available Teacher Names: ";
  for (size_t i = 0; i < teachers.size() && i < 3; i++) {
    if (i > 0) std::cout << ", ";
    std::cout << teachers[i]->getNames() << " " << teachers[i]->getSurnames();
  }
  if (teachers.size() > 3) {
    std::cout << " ... (and " << (teachers.size() - 3) << " more)";
  }
  std::cout << std::endl;

  // Show available course IDs
  const auto& courses = school.getCourses();
  std::cout << "Available Course IDs: ";
  for (size_t i = 0; i < courses.size() && i < 5; i++) {
    if (i > 0) std::cout << ", ";
    std::cout << courses[i]->getId();
  }
  if (courses.size() > 5) {
    std::cout << " ... (and " << (courses.size() - 5) << " more)";
  }
  std::cout << std::endl;
  std::cout << "=======================================" << std::endl;
}

// Comprehensive search menu
void comprehensiveSearchMenu(School& school) {
  showAvailableSearchOptions(school);

  std::cout << "\n--- Comprehensive Search Menu ---" << std::endl;
  std::cout << "1. Search student by ID" << std::endl;
  std::cout << "2. Search teachers by name" << std::endl;
  std::cout << "3. Search students by course" << std::endl;
  std::cout << "4. Search course by ID" << std::endl;
  std::cout << "0. Return to main menu" << std::endl;

  int option;
  std::cout << "Enter your choice: ";
  std::cin >> option;
  clearInputBuffer();

  switch (option) {
    case 1:
      searchStudentById(school);
      break;
    case 2:
      searchTeachersByName(school);
      break;
    case 3:
      searchStudentsByCourse(school);
      break;
    case 4: {
      std::cout << "\n--- Search Course by ID ---" << std::endl;
      std::string courseId = getStringInput("Enter course ID: ");
      Course* course = school.searchCourseById(courseId);

      if (course == nullptr) {
        std::cout << "Course with ID " << courseId << " not found." << std::endl;
      } else {
        std::cout << "\n✓ Course found:" << std::endl;
        std::cout << course->toString() << std::endl;

        auto students = school.searchStudentsByCourse(courseId);
        std::cout << "Students enrolled: " << students.size() << std::endl;
      }
      break;
    }
    case 0:
      return;
    default:
      std::cout << "Invalid option." << std::endl;
      break;
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

  // Create mock data using factory functions
  std::vector<Student*> students = createMockStudents();
  std::vector<Teacher*> teachers = createMockTeachers();
  std::vector<Course*> courses = createMockCourses(teachers);
  std::vector<Assignment*> assignments = createMockAssignments(students, courses);

  // School will take ownership and manage memory through its destructor
  School school(students, teachers, courses, assignments);
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
      case 7:
        assignTeacherToNewCourse(school);
        break;
      case 8:
        seeAllCoursesWithTeachers(school);
        break;
      case 9:
        markAssignmentAsPresented(school);
        break;
      case 10:
        showAssignmentDeliveryStatistics(school);
        break;
      case 11:
        showSpecificTeacherStatistics(school);
        break;
      case 12:
        searchStudentById(school);
        break;
      case 13:
        searchTeachersByName(school);
        break;
      case 14:
        searchStudentsByCourse(school);
        break;
      case 15:
        comprehensiveSearchMenu(school);
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

  // School destructor will automatically clean up all dynamically allocated objects
  return 0;
}
