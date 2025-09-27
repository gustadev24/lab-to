#pragma once
#include <string>
#include "Grade.h"
#include "Person.h"

class Student: public Person {
  private:
    Grade grade;

  public:
    Student(std::string id, Grade grade, std::string names, std::string surnames);
    Student(std::string id);
    Grade getGrade();
    std::string toString() override;
};
