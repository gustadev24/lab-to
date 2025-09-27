#include "Grade.h"

Grade::Grade(std::string id, std::string name) {
    this->id = id;
    this->name = name;
}

std::string Grade::getId() const {
    return this->id;
}

std::string Grade::getName() const {
    return this->name;
}

std::string Grade::toString() const {
    return "Grade{id='" + this->id + "', name='" + this->name + "'}";
}

bool Grade::operator==(const Grade& other) const {
    return this->id == other.id;
}
