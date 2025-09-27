#include "Student.h"

Student::Student(std::string id, Grade grade, std::string names, std::string surnames) {
    this->id = id;
    this->grade = grade;
    this->names = names;
    this->surnames = surnames;
}

std::string Student::getId() {
    return this->id;
}

Grade Student::getGrade() {
    return this->grade;
}

std::string Student::getNames() {
    return this->names;
}

std::string Student::getSurnames() {
    return this->surnames;
}

std::string Student::toString() {
    return this->id + " " + std::to_string(this->grade) + " " + this->names + " " + this->surnames;
}
