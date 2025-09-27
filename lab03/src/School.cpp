#include "School.h"
#include "Assignment.h"
#include "Student.h"
#include "Teacher.h"

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
