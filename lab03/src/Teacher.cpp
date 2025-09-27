#include "Teacher.h"
#include "Grade.h"
#include "Person.h"
#include <optional>

Teacher::Teacher(std::string id, std::string names, std::string surnames, int age): Person(id, names, surnames) {
    this->age = age;
    this->responsibleOf = std::nullopt;
}

Teacher::Teacher(std::string id, std::string names, std::string surnames, int age, const Grade* responsibleOf): Person(id, names, surnames) {
    this->age = age;
    this->responsibleOf = responsibleOf;
}

Teacher::Teacher(std::string id): Person(id) {
    this->age = 0;
    this->responsibleOf = std::nullopt;
}

int Teacher::getAge() {
    return this->age;
}

std::optional<const Grade*> Teacher::getResponsibleOf() {
    return this->responsibleOf;
}

std::string Teacher::toString() {
    std::string result = this->id + " " + this->names + " " + this->surnames + " " + std::to_string(this->age);
    if (this->responsibleOf.has_value()) {
        result += " (Responsible for " + this->responsibleOf.value()->getName() + ")";
    }
    return result;
}
