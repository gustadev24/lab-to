#include "Grade.h"

Grade::Grade(std::string id, std::string name) {
    this->id = id;
    this->name = name;
}

const Grade Grade::FIRST = Grade("1", "First");
const Grade Grade::SECOND = Grade("2", "Second");
const Grade Grade::THIRD = Grade("3", "Third");
const Grade Grade::FOURTH = Grade("4", "Fourth");
const Grade Grade::FIFTH = Grade("5", "Fifth");
const Grade Grade::SIXTH = Grade("6", "Sixth");

std::string Grade::getId() {
    return this->id;
}

std::string Grade::getName() {
    return this->name;
}

std::string Grade::toString() {
    return "Grade{id='" + this->id + "', name='" + this->name + "'}";
}

bool Grade::operator==(const Grade& other) const {
    return this->id == other.id;
}
