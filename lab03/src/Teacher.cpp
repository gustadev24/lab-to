#include "Teacher.h"
#include "Person.h"

Teacher::Teacher(std::string id, std::string names, std::string surnames, int age): Person(id, names, surnames) {
    this->age = age;
    this->responsibleOf = std::nullopt;
}

Teacher::Teacher(std::string id, std::string names, std::string surnames, int age, Grade responsibleOf): Person(id, names, surnames) {
    this->age = age;
    this->responsibleOf = responsibleOf;
}

int Teacher::getAge() {
    return this->age;
}

std::string Teacher::toString() {
    return this->id + " " + this->names + " " + this->surnames + " " + std::to_string(this->age);
}
