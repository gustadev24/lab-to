#include "Student.h"
#include "Person.h"

Student::Student(std::string id, Grade grade, std::string names, std::string surnames): Person(id, names, surnames) {
  this->grade = grade;
}

Grade Student::getGrade() {
    return this->grade;
}

std::string Student::toString() {
    return this->id + " " + std::to_string(this->grade) + " " + this->names + " " + this->surnames;
}
