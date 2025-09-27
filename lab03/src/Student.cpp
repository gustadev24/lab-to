#include "Student.h"
#include "Grade.h"
#include "Person.h"

Student::Student(std::string id, const Grade* grade, std::string names, std::string surnames): Person(id, names, surnames), grade(grade) {}

Student::Student(std::string id): Person(id), grade(&Grade::FIRST) {}

const Grade* Student::getGrade() {
    return this->grade;
}

std::string Student::toString() {
    return this->id + " " + this->grade->getName() + " " + this->names + " " + this->surnames;
}
