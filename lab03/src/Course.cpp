#include "Course.h"
#include <string>

Course::Course(std::string id, Teacher teacher, std::string name, int credits): teacher(teacher) {
    this->id = id;
    this->name = name;
    this->credits = credits;
}

std::string Course::getId() {
    return this->id;
}

Teacher Course::getTeacher() {
    return this->teacher;
}

std::string Course::getName() {
    return this->name;
}

int Course::getCredits() {
    return this->credits;
}

std::string Course::toString() {
    return "Course{id='" + this->id + "', teacher=" + this->teacher.toString() + ", name='" + this->name + "', credits=" + std::to_string(this->credits) + "}";
}
