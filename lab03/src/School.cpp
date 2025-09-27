#include "School.h"
#include "Assignment.h"
#include "Student.h"
#include "Teacher.h"
#include "Grade.h"
#include <iostream>

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

        std::cout << "• Student: " << student->getNames() << " " << student->getSurnames()
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
