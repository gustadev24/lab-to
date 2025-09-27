#pragma once
#include "Grade.h"
#include "Person.h"
#include <optional>
#include <string>

class Teacher: public Person {
  private:
    int age;
    std::optional<Grade> responsibleOf;

  public:
    Teacher(std::string id, std::string names, std::string surnames, int age);
    Teacher(std::string id, std::string names, std::string surnames, int age, Grade responsibleOf);

    int getAge();
    std::optional<Grade> getResponsibleOf();
    std::string toString() override;

};
