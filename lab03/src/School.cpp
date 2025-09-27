#include "School.h"
#include "Assignment.h"
#include "Student.h"
#include "Teacher.h"
#include <algorithm>

School::School(std::vector<Student> students, std::vector<Teacher> teachers, std::vector<Course> courses, std::vector<Assignment> assignments) {
    this->students = students;
    this->teachers = teachers;
    this->courses = courses;
    this->assignments = assignments;
}

const std::vector<Student>& School::getStudents() {
    return this->students;
}

const std::vector<Teacher>& School::getTeachers() {
    return this->teachers;
}

const std::vector<Course>& School::getCourses() {
    return this->courses;
}

const std::vector<Assignment>& School::getAssignments() {
    return this->assignments;
}

void School::addStudent(Student student) {
    this->students.push_back(student);
}

void School::addTeacher(Teacher teacher) {
    this->teachers.push_back(teacher);
}

void School::addCourse(Course course) {
    this->courses.push_back(course);
}

void School::addAssignment(Assignment assignment) {
    this->assignments.push_back(assignment);
}

const std::vector<Assignment> School::getPresentedAssignmentsByStudentId(const std::string& studentId) const {
    std::vector<Assignment> presentedAssignments;
    for (Assignment assignment : this->assignments) {
        if (assignment.getStudent().getId() == studentId && assignment.isPresented()) {
            presentedAssignments.push_back(assignment);
        }
    }
    return presentedAssignments;
}

const std::vector<Student> School::getStudentsByTeacherId(const std::string& teacherId) const {
    std::vector<Student> studentsByTeacher;
    auto it = std::find(this->teachers.begin(), this->teachers.end(), Teacher(teacherId));
    if (it == this->teachers.end()) {
        return studentsByTeacher; // empty
    }
    Teacher teacher = *it;
    Grade grade = teacher.getResponsibleOf().value_or(Grade::FIRST);
    for (Student student : this->students) {
        if (student.getGrade() == grade) {
            studentsByTeacher.push_back(student);
        }
    }
    return studentsByTeacher;
}
