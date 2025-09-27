#pragma once
#include "Grade.h"
#include <optional>
#include <string>

class Teacher {
  private:
    std::string id;
    std::string names;
    std::string surnames;
    int age;
    std::optional<Grade> responsibleOf;

  public:
    Teacher(std::string id, std::string names, std::string surnames, int age, std::optional<Grade> responsibleOf = std::nullopt);
    std::string getId();
    std::string getNames();
    std::string getSurnames();
    int getAge();
    std::optional<Grade> getResponsibleOf();
    std::string toString();
};
