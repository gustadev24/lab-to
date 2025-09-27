#include "Teacher.h"

Teacher::Teacher(std::string id, std::string names, std::string surnames, int age) {
    this->id = id;
    this->names = names;
    this->surnames = surnames;
    this->age = age;
}

std::string Teacher::getId() {
    return this->id;
}

std::string Teacher::getNames() {
    return this->names;
}

std::string Teacher::getSurnames() {
    return this->surnames;
}

int Teacher::getAge() {
    return this->age;
}

std::string Teacher::toString() {
    return this->id + " " + this->names + " " + this->surnames + " " + std::to_string(this->age);
}
