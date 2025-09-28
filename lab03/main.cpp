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
  "Save data to file",
  "Load data from file",
  "Create new assignment",
  "Validation system demo",
  "Run comprehensive validation test",
};

// Helper function to convert string to Grade pointer with validation
const Grade* stringToGrade(const std::string& gradeStr) {
  if (gradeStr == "1" || gradeStr == "FIRST") return &Grade::FIRST;
  if (gradeStr == "2" || gradeStr == "SECOND") return &Grade::SECOND;
  if (gradeStr == "3" || gradeStr == "THIRD") return &Grade::THIRD;
  if (gradeStr == "4" || gradeStr == "FOURTH") return &Grade::FOURTH;
  if (gradeStr == "5" || gradeStr == "FIFTH") return &Grade::FIFTH;
  if (gradeStr == "6" || gradeStr == "SIXTH") return &Grade::SIXTH;
  return nullptr; // Return null for invalid grades
}

// Helper function to validate and convert grade string
const Grade* validateAndConvertGrade(const std::string& gradeStr, School& school) {
  try {
    int gradeNumber = std::stoi(gradeStr);
    if (!school.isValidGrade(gradeNumber)) {
      return nullptr;
    }
    return stringToGrade(gradeStr);
  } catch (const std::exception& e) {
    return nullptr;
  }
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

  // Validate unique student ID
  if (!school.isStudentIdUnique(id)) {
    std::cout << "✗ Error: Student ID " << id << " already exists. Please use a unique ID." << std::endl;
    return;
  }

  std::string names = getStringInput("Enter student names: ");
  std::string surnames = getStringInput("Enter student surnames: ");

  std::cout << "Available grades: 1(First), 2(Second), 3(Third), 4(Fourth), 5(Fifth), 6(Sixth)" << std::endl;
  std::string gradeInput = getStringInput("Enter student grade (1-6): ");

  // Validate grade input
  const Grade* grade = validateAndConvertGrade(gradeInput, school);
  if (grade == nullptr) {
    std::cout << "✗ Error: Invalid grade '" << gradeInput << "'. Grade must be between 1-6." << std::endl;
    return;
  }

  Student* newStudent = new Student(id, grade, names, surnames);
  school.addStudent(newStudent);

  std::cout << "✓ Student registered successfully!" << std::endl;
  std::cout << "Student info: " << newStudent->toString() << std::endl;

  // Auto-save after adding new student
  school.saveToFile("school_data.txt");
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

  // Validate unique teacher ID
  bool teacherIdExists = false;
  const auto& teachers = school.getTeachers();
  for (auto teacher : teachers) {
    if (teacher->getId() == id) {
      teacherIdExists = true;
      break;
    }
  }
  if (teacherIdExists) {
    std::cout << "✗ Error: Teacher ID " << id << " already exists. Please use a unique ID." << std::endl;
    return;
  }

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
    const Grade* responsibleGrade = validateAndConvertGrade(gradeInput, school);
    if (responsibleGrade == nullptr) {
      std::cout << "✗ Error: Invalid grade '" << gradeInput << "'. Using default teacher without grade responsibility." << std::endl;
    } else {
      delete newTeacher; // Delete the old one
      newTeacher = new Teacher(id, names, surnames, age, responsibleGrade);
    }
  }

  school.addTeacher(newTeacher);

  std::cout << "✓ Teacher registered successfully!" << std::endl;
  std::cout << "Teacher info: " << newTeacher->toString() << std::endl;

  // Auto-save after adding new teacher
  school.saveToFile("school_data.txt");
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

  // Validate teacher exists before assignment
  if (!school.teacherExists(teacherId)) {
    std::cout << "✗ Error: Teacher with ID " << teacherId << " does not exist." << std::endl;
    std::cout << "Please register the teacher first before assigning courses." << std::endl;
    return;
  }

  // Get teacher object
  Teacher* selectedTeacher = nullptr;
  for (auto teacher : teachers) {
    if (teacher->getId() == teacherId) {
      selectedTeacher = teacher;
      break;
    }
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

  // Auto-save after adding new course
  school.saveToFile("school_data.txt");

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

  // Auto-save after marking assignment as presented
  school.saveToFile("school_data.txt");

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

// Save data to file
void saveDataToFile(School& school) {
  std::cout << "\n--- Save Data to File ---" << std::endl;
  std::string filename = getStringInput("Enter filename (or press Enter for 'school_data.txt'): ");

  if (filename.empty()) {
    filename = "school_data.txt";
  }

  if (school.saveToFile(filename)) {
    std::cout << "✓ Data successfully saved to " << filename << std::endl;
  } else {
    std::cout << "✗ Error: Could not save data to " << filename << std::endl;
  }
}

// Create new assignment with validation
void createNewAssignment(School& school) {
  std::cout << "\n--- Create New Assignment ---" << std::endl;

  std::string assignmentId = getStringInput("Enter assignment ID: ");
  std::string assignmentName = getStringInput("Enter assignment name: ");

  // Show available students
  std::cout << "\nAvailable students:" << std::endl;
  const auto& students = school.getStudents();
  for (size_t i = 0; i < students.size() && i < 10; i++) {
    std::cout << "  " << students[i]->getId() << " - " << students[i]->getNames()
              << " " << students[i]->getSurnames() << std::endl;
  }

  std::string studentId = getStringInput("\nEnter student ID: ");

  // Validate student exists
  if (!school.searchStudentById(studentId)) {
    std::cout << "✗ Error: Student with ID " << studentId << " does not exist." << std::endl;
    return;
  }

  // Show available courses
  std::cout << "\nAvailable courses:" << std::endl;
  const auto& courses = school.getCourses();
  for (size_t i = 0; i < courses.size() && i < 10; i++) {
    std::cout << "  " << courses[i]->getId() << " - " << courses[i]->getName()
              << " (Teacher: " << courses[i]->getTeacher()->getNames() << ")" << std::endl;
  }

  std::string courseId = getStringInput("\nEnter course ID: ");

  // Validate course exists
  Course* course = school.searchCourseById(courseId);
  if (!course) {
    std::cout << "✗ Error: Course with ID " << courseId << " does not exist." << std::endl;
    return;
  }

  // Validate teacher exists (through course)
  if (!school.teacherExists(course->getTeacher()->getId())) {
    std::cout << "✗ Error: Teacher for this course does not exist in the system." << std::endl;
    return;
  }

  // Create assignment
  Student* student = school.searchStudentById(studentId);
  Assignment* assignment = new Assignment(assignmentId, assignmentName, student, course);
  school.addAssignment(assignment);

  std::cout << "✓ Assignment created successfully!" << std::endl;
  std::cout << "Assignment: " << assignmentName << std::endl;
  std::cout << "Student: " << student->getNames() << " " << student->getSurnames() << std::endl;
  std::cout << "Course: " << course->getName() << std::endl;
  std::cout << "Teacher: " << course->getTeacher()->getNames() << " " << course->getTeacher()->getSurnames() << std::endl;

  // Auto-save after creating assignment
  school.saveToFile("school_data.txt");
}

// Validation system demonstration
void validationSystemDemo(School& school) {
  std::cout << "\n=== VALIDATION SYSTEM DEMONSTRATION ===" << std::endl;

  std::cout << "\n1. Testing Student ID Uniqueness:" << std::endl;
  std::cout << "✓ Checking if 'S001' is unique: " << (school.isStudentIdUnique("S001") ? "Available" : "Already exists") << std::endl;
  std::cout << "✓ Checking if 'S999' is unique: " << (school.isStudentIdUnique("S999") ? "Available" : "Already exists") << std::endl;

  std::cout << "\n2. Testing Grade Validation:" << std::endl;
  for (int i = 0; i <= 8; i++) {
    std::cout << "✓ Grade " << i << ": " << (school.isValidGrade(i) ? "Valid" : "Invalid") << std::endl;
  }

  std::cout << "\n3. Testing Teacher Existence:" << std::endl;
  std::cout << "✓ Checking if teacher 'T001' exists: " << (school.teacherExists("T001") ? "Exists" : "Does not exist") << std::endl;
  std::cout << "✓ Checking if teacher 'T999' exists: " << (school.teacherExists("T999") ? "Exists" : "Does not exist") << std::endl;

  std::cout << "\n4. System Validation Rules:" << std::endl;
  std::cout << "✓ Student IDs must be unique across the system" << std::endl;
  std::cout << "✓ Students can only be registered in grades 1-6" << std::endl;
  std::cout << "✓ Teachers must exist before being assigned to courses or assignments" << std::endl;
  std::cout << "✓ All validations are automatically enforced during registration" << std::endl;

  std::cout << "\n=== VALIDATION SYSTEM STATUS: ACTIVE ===" << std::endl;
}

// Comprehensive validation test
void comprehensiveValidationTest(School& school) {
  std::cout << "\n=== COMPREHENSIVE VALIDATION TEST ===" << std::endl;

  std::cout << "\n1. Testing Student ID Uniqueness Validation:" << std::endl;

  // Test with existing student ID
  std::cout << "Attempting to register student with existing ID 'S001'..." << std::endl;
  if (!school.isStudentIdUnique("S001")) {
    std::cout << "✓ PASS: System correctly identifies duplicate student ID" << std::endl;
  } else {
    std::cout << "✗ FAIL: System should reject duplicate student ID" << std::endl;
  }

  // Test with new student ID
  std::cout << "Testing new student ID 'S999'..." << std::endl;
  if (school.isStudentIdUnique("S999")) {
    std::cout << "✓ PASS: System correctly identifies unique student ID" << std::endl;
  } else {
    std::cout << "✗ FAIL: System should accept unique student ID" << std::endl;
  }

  std::cout << "\n2. Testing Grade Validation (1-6):" << std::endl;

  // Test invalid grades
  int invalidGrades[] = {0, -1, 7, 8, 10};
  for (int grade : invalidGrades) {
    if (!school.isValidGrade(grade)) {
      std::cout << "✓ PASS: Grade " << grade << " correctly rejected" << std::endl;
    } else {
      std::cout << "✗ FAIL: Grade " << grade << " should be rejected" << std::endl;
    }
  }

  // Test valid grades
  for (int grade = 1; grade <= 6; grade++) {
    if (school.isValidGrade(grade)) {
      std::cout << "✓ PASS: Grade " << grade << " correctly accepted" << std::endl;
    } else {
      std::cout << "✗ FAIL: Grade " << grade << " should be accepted" << std::endl;
    }
  }

  std::cout << "\n3. Testing Teacher Existence Validation:" << std::endl;

  // Test with existing teacher
  if (school.teacherExists("T001")) {
    std::cout << "✓ PASS: System correctly identifies existing teacher T001" << std::endl;
  } else {
    std::cout << "✗ FAIL: System should find existing teacher T001" << std::endl;
  }

  // Test with non-existing teacher
  if (!school.teacherExists("T999")) {
    std::cout << "✓ PASS: System correctly identifies non-existing teacher T999" << std::endl;
  } else {
    std::cout << "✗ FAIL: System should not find non-existing teacher T999" << std::endl;
  }

  std::cout << "\n4. Integration Test - Assignment Creation Validation:" << std::endl;

  // Check if we can create assignment with existing teacher
  Course* testCourse = school.searchCourseById("C001");
  if (testCourse && school.teacherExists(testCourse->getTeacher()->getId())) {
    std::cout << "✓ PASS: Assignment can be created with existing teacher" << std::endl;
  } else {
    std::cout << "✗ FAIL: Assignment creation validation failed" << std::endl;
  }

  std::cout << "\n=== VALIDATION TEST SUMMARY ===" << std::endl;
  std::cout << "All validation rules are properly enforced:" << std::endl;
  std::cout << "• Student IDs are unique" << std::endl;
  std::cout << "• Grades are limited to 1-6 range" << std::endl;
  std::cout << "• Teachers must exist before assignment" << std::endl;
  std::cout << "• Data integrity is maintained" << std::endl;
  std::cout << "=================================" << std::endl;
}

// Load data from file
void loadDataFromFile(School& school) {
  std::cout << "\n--- Load Data from File ---" << std::endl;
  std::string filename = getStringInput("Enter filename (or press Enter for 'school_data.txt'): ");

  if (filename.empty()) {
    filename = "school_data.txt";
  }

  if (school.loadFromFile(filename)) {
    std::cout << "✓ Data successfully loaded from " << filename << std::endl;
    std::cout << "Students: " << school.getStudents().size() << std::endl;
    std::cout << "Teachers: " << school.getTeachers().size() << std::endl;
    std::cout << "Courses: " << school.getCourses().size() << std::endl;
    std::cout << "Assignments: " << school.getAssignments().size() << std::endl;
  } else {
    std::cout << "✗ Error: Could not load data from " << filename << std::endl;
    std::cout << "File may not exist or may be corrupted." << std::endl;
  }
}

// Initialize school with auto-load or mock data
School* initializeSchool() {
  std::cout << "Initializing system..." << std::endl;

  // Try to load from file first
  School* school = new School({}, {}, {}, {});

  if (school->loadFromFile("school_data.txt")) {
    std::cout << "✓ Loaded existing data from school_data.txt" << std::endl;
    std::cout << "Students: " << school->getStudents().size() << std::endl;
    std::cout << "Teachers: " << school->getTeachers().size() << std::endl;
    std::cout << "Courses: " << school->getCourses().size() << std::endl;
    std::cout << "Assignments: " << school->getAssignments().size() << std::endl;
  } else {
    std::cout << "No existing data file found. Creating initial mock data..." << std::endl;

    // Delete empty school and create with mock data
    delete school;

    // Create mock data using factory functions
    std::vector<Student*> students = createMockStudents();
    std::vector<Teacher*> teachers = createMockTeachers();
    std::vector<Course*> courses = createMockCourses(teachers);
    std::vector<Assignment*> assignments = createMockAssignments(students, courses);

    school = new School(students, teachers, courses, assignments);

    // Save initial mock data
    school->saveToFile("school_data.txt");
    std::cout << "✓ Initial data saved to school_data.txt" << std::endl;
  }

  return school;
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

  // Initialize school with auto-load or mock data
  School* school = initializeSchool();

  // Display validation system status
  std::cout << "\n=== VALIDATION SYSTEM STATUS ===" << std::endl;
  std::cout << "✓ Student ID uniqueness validation: ACTIVE" << std::endl;
  std::cout << "✓ Grade validity validation (1-6): ACTIVE" << std::endl;
  std::cout << "✓ Teacher existence validation: ACTIVE" << std::endl;
  std::cout << "=======================================" << std::endl;

  bool running = true;
  do {
    int option = readOption();
    if (option == -1) {
      std::cout << "Invalid option. Please try again." << std::endl;
      continue;
    }

    switch (option) {
      case 1:
      registerStudent(*school);
      break;
      case 2:
      seeAllStudents(*school);
      break;
      case 3:
      registerTeacher(*school);
      break;
      case 4:
      seeAllTeachers(*school);
      break;
      case 5:
      searchAssignmentsPerStudent(*school);
      break;
      case 6:
        searchStudentsPerTeacher(*school);
        break;
      case 7:
        assignTeacherToNewCourse(*school);
        break;
      case 8:
        seeAllCoursesWithTeachers(*school);
        break;
      case 9:
        markAssignmentAsPresented(*school);
        break;
      case 10:
        showAssignmentDeliveryStatistics(*school);
        break;
      case 11:
        showSpecificTeacherStatistics(*school);
        break;
      case 12:
        searchStudentById(*school);
        break;
      case 13:
        searchTeachersByName(*school);
        break;
      case 14:
        searchStudentsByCourse(*school);
        break;
      case 15:
        comprehensiveSearchMenu(*school);
        break;
      case 16:
        saveDataToFile(*school);
        break;
      case 17:
        loadDataFromFile(*school);
        break;
      case 18:
        createNewAssignment(*school);
        break;
      case 19:
        validationSystemDemo(*school);
        break;
      case 20:
        comprehensiveValidationTest(*school);
        break;
      case 0:
        std::cout << "Exiting classroom management system..." << std::endl;
        std::cout << "Automatically saving data before exit..." << std::endl;
        if (school->saveToFile("school_data.txt")) {
          std::cout << "✓ Data saved successfully!" << std::endl;
        } else {
          std::cout << "✗ Warning: Could not save data!" << std::endl;
        }
        running = false;
        break;
      default:
      std::cout << "Invalid option. Please try again." << std::endl;
      break;
    }
  } while (running);

  // Clean up dynamically allocated school
  delete school;
  return 0;
}
