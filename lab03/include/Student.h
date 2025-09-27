#pragma once
#include <string>
#include "Person.h"

class Grade;

class Student: public Person {
  private:
    const Grade* grade;

  public:
    Student(std::string id, const Grade* grade, std::string names, std::string surnames);
    Student(std::string id);
    const Grade* getGrade();
    std::string toString() override;
};
