#include "Grade.h"

Grade::Grade(std::string id, std::string name) {
    this->id = id;
    this->name = name;
}

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
