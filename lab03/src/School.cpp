#include "School.h"
#include "Assignment.h"
#include "Student.h"
#include "Teacher.h"
#include "Grade.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

School::School(std::vector<Student*> students, std::vector<Teacher*> teachers, std::vector<Course*> courses, std::vector<Assignment*> assignments) {
    this->students = students;
    this->teachers = teachers;
    this->courses = courses;
    this->assignments = assignments;
}

School::~School() {
    for (Student* student : this->students) {
        delete student;
    }
    for (Teacher* teacher : this->teachers) {
        delete teacher;
    }
    for (Course* course : this->courses) {
        delete course;
    }
    for (Assignment* assignment : this->assignments) {
        delete assignment;
    }
}

const std::vector<Student*>& School::getStudents() {
    return this->students;
}

const std::vector<Teacher*>& School::getTeachers() {
    return this->teachers;
}

const std::vector<Course*>& School::getCourses() {
    return this->courses;
}

const std::vector<Assignment*>& School::getAssignments() {
    return this->assignments;
}

void School::addStudent(Student* student) {
    this->students.push_back(student);
}

void School::addTeacher(Teacher* teacher) {
    this->teachers.push_back(teacher);
}

void School::addCourse(Course* course) {
    this->courses.push_back(course);
}

void School::addAssignment(Assignment* assignment) {
    this->assignments.push_back(assignment);
}

const std::vector<Assignment*> School::getPresentedAssignmentsByStudentId(const std::string& studentId) const {
    std::vector<Assignment*> presentedAssignments;
    for (Assignment* assignment : this->assignments) {
        if (assignment->getStudent()->getId() == studentId && assignment->isPresented()) {
            presentedAssignments.push_back(assignment);
        }
    }
    return presentedAssignments;
}

const std::vector<Student*> School::getStudentsByTeacherId(const std::string& teacherId) const {
    std::vector<Student*> studentsByTeacher;
    Teacher* foundTeacher = nullptr;

    for (Teacher* teacher : this->teachers) {
        if (teacher->getId() == teacherId) {
            foundTeacher = teacher;
            break;
        }
    }

    if (foundTeacher == nullptr) {
        return studentsByTeacher; // empty
    }

    if (!foundTeacher->getResponsibleOf().has_value()) {
        return studentsByTeacher; // empty if teacher is not responsible for any grade
    }

    const Grade* grade = foundTeacher->getResponsibleOf().value();
    for (Student* student : this->students) {
        if (student->getGrade() == grade) {
            studentsByTeacher.push_back(student);
        }
    }
    return studentsByTeacher;
}

const std::vector<Course*> School::getCoursesByTeacherId(const std::string& teacherId) const {
    std::vector<Course*> coursesByTeacher;

    for (Course* course : this->courses) {
        if (course->getTeacher()->getId() == teacherId) {
            coursesByTeacher.push_back(course);
        }
    }

    return coursesByTeacher;
}

const std::vector<Assignment*> School::getAllAssignmentsByStudentId(const std::string& studentId) const {
    std::vector<Assignment*> allAssignments;
    for (Assignment* assignment : this->assignments) {
        if (assignment->getStudent()->getId() == studentId) {
            allAssignments.push_back(assignment);
        }
    }
    return allAssignments;
}

void School::showAssignmentDeliveryStatistics() const {
    std::cout << "\n=== ASSIGNMENT DELIVERY STATISTICS ===" << std::endl;

    // Show statistics per student
    std::cout << "\n--- STUDENTS' ASSIGNMENT DELIVERY ---" << std::endl;
    for (Student* student : this->students) {
        std::string studentId = student->getId();
        auto studentAssignments = getAllAssignmentsByStudentId(studentId);

        int deliveredCount = 0;
        for (Assignment* assignment : studentAssignments) {
            if (assignment->isPresented()) {
                deliveredCount++;
            }
        }

        double deliveryPercentage = 0.0;
        if (!studentAssignments.empty()) {
            deliveryPercentage = (double)deliveredCount / studentAssignments.size() * 100.0;
        }

        std::cout << "• Student: " << student->getNames() << " "
 << student->getSurnames()
                  << " (ID: " << studentId << ")" << std::endl;
        std::cout << "  Delivered assignments: " << deliveredCount << "/"
                  << studentAssignments.size() << std::endl;
        std::cout << "  Delivery percentage: " << deliveryPercentage << "%" << std::endl;
        std::cout << std::endl;
    }

    // Show teacher statistics
    std::cout << "--- TEACHERS' STUDENT RESPONSIBILITY ---" << std::endl;
    for (Teacher* teacher : this->teachers) {
        std::string teacherId = teacher->getId();
        auto studentsUnderTeacher = getStudentsByTeacherId(teacherId);

        std::cout << "• Teacher: " << teacher->getNames() << " " << teacher->getSurnames()
                  << " (ID: " << teacherId << ")" << std::endl;
        std::cout << "  Total students under responsibility: " << studentsUnderTeacher.size() << std::endl;

        if (teacher->getResponsibleOf().has_value()) {
            std::cout << "  Responsible for grade: " << teacher->getResponsibleOf().value()->getName() << std::endl;
        } else {
            std::cout << "  Not responsible for any specific grade" << std::endl;
        }
        std::cout << std::endl;
    }

    // Show overall statistics
    std::cout << "--- OVERALL STATISTICS ---" << std::endl;
    int totalAssignments = this->assignments.size();
    int totalDeliveredAssignments = 0;

    for (Assignment* assignment : this->assignments) {
        if (assignment->isPresented()) {
            totalDeliveredAssignments++;
        }
    }

    double overallDeliveryRate = 0.0;
    if (totalAssignments > 0) {
        overallDeliveryRate = (double)totalDeliveredAssignments / totalAssignments * 100.0;
    }

    std::cout << "Total assignments in system: " << totalAssignments << std::endl;
    std::cout << "Total delivered assignments: " << totalDeliveredAssignments << std::endl;
    std::cout << "Overall delivery rate: " << overallDeliveryRate << "%" << std::endl;
    std::cout << "Total students: " << this->students.size() << std::endl;
    std::cout << "Total teachers: " << this->teachers.size() << std::endl;

    std::cout << "=======================================" << std::endl;
}

void School::showTeacherStatistics(const std::string& teacherId) const {
    std::cout << "\n=== TEACHER STATISTICS ===" << std::endl;

    // Find the teacher
    Teacher* teacher = nullptr;
    for (Teacher* t : this->teachers) {
        if (t->getId() == teacherId) {
            teacher = t;
            break;
        }
    }

    if (teacher == nullptr) {
        std::cout << "Teacher with ID " << teacherId << " not found." << std::endl;
        return;
    }

    std::cout << "Teacher: " << teacher->getNames() << " " << teacher->getSurnames()
              << " (ID: " << teacherId << ")" << std::endl;

    // Get students under this teacher's responsibility
    auto studentsUnderTeacher = getStudentsByTeacherId(teacherId);
    std::cout << "Total students under responsibility: " << studentsUnderTeacher.size() << std::endl;

    if (teacher->getResponsibleOf().has_value()) {
        std::cout << "Responsible for grade: " << teacher->getResponsibleOf().value()->getName() << std::endl;
    } else {
        std::cout << "Not responsible for any specific grade" << std::endl;
    }

    // Show courses taught by this teacher
    auto coursesTaught = getCoursesByTeacherId(teacherId);
    std::cout << "Courses taught: " << coursesTaught.size() << std::endl;
    for (Course* course : coursesTaught) {
        std::cout << "  - " << course->getName() << " (" << course->getId() << ")" << std::endl;
    }

    // Show assignment statistics for students under this teacher
    if (!studentsUnderTeacher.empty()) {
        std::cout << "\n--- ASSIGNMENT STATISTICS FOR STUDENTS UNDER THIS TEACHER ---" << std::endl;
        int totalAssignmentsForStudents = 0;
        int totalDeliveredForStudents = 0;

        for (Student* student : studentsUnderTeacher) {
            auto studentAssignments = getAllAssignmentsByStudentId(student->getId());
            int deliveredCount = 0;

            for (Assignment* assignment : studentAssignments) {
                if (assignment->isPresented()) {
                    deliveredCount++;
                }
            }

            totalAssignmentsForStudents += studentAssignments.size();
            totalDeliveredForStudents += deliveredCount;

            double deliveryPercentage = 0.0;
            if (!studentAssignments.empty()) {
                deliveryPercentage = (double)deliveredCount / studentAssignments.size() * 100.0;
            }

            std::cout << "  • " << student->getNames() << " " << student->getSurnames()
                      << ": " << deliveredCount << "/" << studentAssignments.size()
                      << " (" << deliveryPercentage << "%)" << std::endl;
        }

        double overallTeacherRate = 0.0;
        if (totalAssignmentsForStudents > 0) {
            overallTeacherRate = (double)totalDeliveredForStudents / totalAssignmentsForStudents * 100.0;
        }

        std::cout << "\nOverall delivery rate for students under this teacher: "
                  << overallTeacherRate << "% (" << totalDeliveredForStudents
                  << "/" << totalAssignmentsForStudents << ")" << std::endl;
    }

    std::cout << "=======================================" << std::endl;
}

Student* School::searchStudentById(const std::string& studentId) const {
    for (Student* student : this->students) {
        if (student->getId() == studentId) {
            return student;
        }
    }
    return nullptr;
}

std::vector<Teacher*> School::searchTeachersByName(const std::string& teacherName) const {
    std::vector<Teacher*> foundTeachers;

    for (Teacher* teacher : this->teachers) {
        std::string fullName = teacher->getNames() + " " + teacher->getSurnames();

        // Check if the search name is contained in full name (case insensitive)
        std::string searchLower = teacherName;
        std::string fullNameLower = fullName;

        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
        std::transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);

        if (fullNameLower.find(searchLower) != std::string::npos) {
            foundTeachers.push_back(teacher);
        }
    }

    return foundTeachers;
}

std::vector<Student*> School::searchStudentsByCourse(const std::string& courseId) const {
    std::vector<Student*> studentsInCourse;

    // Find all assignments for this course and collect unique students
    for (Assignment* assignment : this->assignments) {
        if (assignment->getCourse()->getId() == courseId) {
            Student* student = assignment->getStudent();

            // Check if student is already in the list to avoid duplicates
            bool alreadyAdded = false;
            for (Student* existingStudent : studentsInCourse) {
                if (existingStudent->getId() == student->getId()) {
                    alreadyAdded = true;
                    break;
                }
            }

            if (!alreadyAdded) {
                studentsInCourse.push_back(student);
            }
        }
    }

    return studentsInCourse;
}

Course* School::searchCourseById(const std::string& courseId) const {
    for (Course* course : this->courses) {
        if (course->getId() == courseId) {
            return course;
        }
    }
    return nullptr;
}

bool School::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Save students
    file << "[STUDENTS]" << std::endl;
    for (Student* student : this->students) {
        file << student->getId() << "|"
             << student->getGrade()->getId() << "|"
             << student->getNames() << "|"
             << student->getSurnames() << std::endl;
    }

    // Save teachers
    file << "[TEACHERS]" << std::endl;
    for (Teacher* teacher : this->teachers) {
        file << teacher->getId() << "|"
             << teacher->getNames() << "|"
             << teacher->getSurnames() << "|"
             << teacher->getAge() << "|";

        if (teacher->getResponsibleOf().has_value()) {
            file << teacher->getResponsibleOf().value()->getId();
        } else {
            file << "NONE";
        }
        file << std::endl;
    }

    // Save courses
    file << "[COURSES]" << std::endl;
    for (Course* course : this->courses) {
        file << course->getId() << "|"
             << course->getTeacher()->getId() << "|"
             << course->getName() << "|"
             << course->getCredits() << std::endl;
    }

    // Save assignments
    file << "[ASSIGNMENTS]" << std::endl;
    for (Assignment* assignment : this->assignments) {
        file << assignment->getId() << "|"
             << assignment->getName() << "|"
             << assignment->getStudent()->getId() << "|"
             << assignment->getCourse()->getId() << "|"
             << (assignment->isPresented() ? "1" : "0") << "|";

        if (assignment->getPresentationDate().has_value()) {
            file << assignment->getPresentationDate().value();
        } else {
            file << "NONE";
        }
        file << std::endl;
    }

    file.close();
    return true;
}

bool School::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    clearData();

    std::string line;
    std::string currentSection = "";

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line == "[STUDENTS]") {
            currentSection = "STUDENTS";
            continue;
        } else if (line == "[TEACHERS]") {
            currentSection = "TEACHERS";
            continue;
        } else if (line == "[COURSES]") {
            currentSection = "COURSES";
            continue;
        } else if (line == "[ASSIGNMENTS]") {
            currentSection = "ASSIGNMENTS";
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        if (currentSection == "STUDENTS") {
            std::vector<std::string> tokens;
            while (std::getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 4) {
                const Grade* grade = nullptr;
                if (tokens[1] == "1") grade = &Grade::FIRST;
                else if (tokens[1] == "2") grade = &Grade::SECOND;
                else if (tokens[1] == "3") grade = &Grade::THIRD;
                else if (tokens[1] == "4") grade = &Grade::FOURTH;
                else if (tokens[1] == "5") grade = &Grade::FIFTH;
                else if (tokens[1] == "6") grade = &Grade::SIXTH;
                else grade = &Grade::FIRST;

                Student* student = new Student(tokens[0], grade, tokens[2], tokens[3]);
                this->students.push_back(student);
            }
        } else if (currentSection == "TEACHERS") {
            std::vector<std::string> tokens;
            while (std::getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 5) {
                Teacher* teacher;
                if (tokens[4] != "NONE") {
                    const Grade* grade = nullptr;
                    if (tokens[4] == "1") grade = &Grade::FIRST;
                    else if (tokens[4] == "2") grade = &Grade::SECOND;
                    else if (tokens[4] == "3") grade = &Grade::THIRD;
                    else if (tokens[4] == "4") grade = &Grade::FOURTH;
                    else if (tokens[4] == "5") grade = &Grade::FIFTH;
                    else if (tokens[4] == "6") grade = &Grade::SIXTH;

                    teacher = new Teacher(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]), grade);
                } else {
                    teacher = new Teacher(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]));
                }
                this->teachers.push_back(teacher);
            }
        } else if (currentSection == "COURSES") {
            std::vector<std::string> tokens;
            while (std::getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 4) {
                // Find teacher by ID
                Teacher* teacher = nullptr;
                for (Teacher* t : this->teachers) {
                    if (t->getId() == tokens[1]) {
                        teacher = t;
                        break;
                    }
                }
                if (teacher) {
                    Course* course = new Course(tokens[0], teacher, tokens[2], std::stoi(tokens[3]));
                    this->courses.push_back(course);
                }
            }
        } else if (currentSection == "ASSIGNMENTS") {
            std::vector<std::string> tokens;
            while (std::getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 6) {
                // Find student by ID
                Student* student = nullptr;
                for (Student* s : this->students) {
                    if (s->getId() == tokens[2]) {
                        student = s;
                        break;
                    }
                }

                // Find course by ID
                Course* course = nullptr;
                for (Course* c : this->courses) {
                    if (c->getId() == tokens[3]) {
                        course = c;
                        break;
                    }
                }

                if (student && course) {
                    Assignment* assignment = new Assignment(tokens[0], tokens[1], student, course);

                    // Set presentation status
                    if (tokens[4] == "1") {
                        assignment->present();
                    }

                    this->assignments.push_back(assignment);
                }
            }
        }
    }

    file.close();
    return true;
}

void School::clearData() {
    // Delete all assignments
    for (Assignment* assignment : this->assignments) {
        delete assignment;
    }
    this->assignments.clear();

    // Delete all courses
    for (Course* course : this->courses) {
        delete course;
    }
    this->courses.clear();

    // Delete all teachers
    for (Teacher* teacher : this->teachers) {
        delete teacher;
    }
    this->teachers.clear();

    // Delete all students
    for (Student* student : this->students) {
        delete student;
    }
    this->students.clear();
}
