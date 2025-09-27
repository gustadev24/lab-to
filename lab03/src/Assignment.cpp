#include "Assignment.h"
#include "Student.h"
#include "Course.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

Assignment::Assignment(std::string id, std::string name, Student* student, Course* course) : student(student), course(course) {
    this->id = id;
    this->name = name;
    this->_isPresented = false;
    this->presentationDate = std::nullopt;
}

std::string Assignment::getId() {
    return this->id;
}

std::string Assignment::getName() {
    return this->name;
}

std::optional<std::string> Assignment::getPresentationDate() {
    return this->presentationDate;
}

bool Assignment::isPresented() {
    return this->_isPresented;
}

Student* Assignment::getStudent() {
    return this->student;
}

Course* Assignment::getCourse() {
    return this->course;
}

void Assignment::present() {
    this->_isPresented = true;
    // Now time to set the presentation date to current date in format "YYYY-MM-DD"
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);

    std::ostringstream oss;

    oss << std::put_time(ltm, "%Y-%m-%d");

    this->presentationDate = oss.str();
}
