#pragma once
#include "Person.h"
#include <optional>
#include <string>

class Grade;

class Teacher: public Person {
  private:
    int age;
    std::optional<const Grade*> responsibleOf;

  public:
    Teacher(std::string id, std::string names, std::string surnames, int age);
    Teacher(std::string id, std::string names, std::string surnames, int age, const Grade* responsibleOf);
    Teacher(std::string id);

    int getAge();
    std::optional<const Grade*> getResponsibleOf();
    std::string toString() override;

};
