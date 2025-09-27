#pragma once
#include <string>

class Teacher;

class Course {
  private:
    std::string id;
    Teacher* teacher;
    std::string name;
    int credits;

  public:
    Course(std::string id, Teacher* teacher, std::string name, int credits);
    std::string getId();
    Teacher* getTeacher();
    std::string getName();
    int getCredits();
    std::string toString();
};
