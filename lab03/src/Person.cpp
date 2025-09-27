#include "Person.h"

Person::Person(std::string id, std::string names, std::string surnames) {
    this->id = id;
    this->names = names;
    this->surnames = surnames;
}

std::string Person::getId() {
    return this->id;
}

std::string Person::getNames() {
    return this->names;
}

std::string Person::getSurnames() {
    return this->surnames;
}

std::string Person::toString() {
    return "Person{id='" + this->id + "', names='" + this->names + "', surnames='" + this->surnames + "'}";
}

bool Person::operator==(const Person& other) const {
    return this->id == other.id;
}
