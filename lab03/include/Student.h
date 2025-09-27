#include <string>
#include "Grade.h"

class Student {
  private:
    std::string id;
    Grade grade;
    std::string names;
    std::string surnames;

  public:
    Student(std::string id, Grade grade, std::string names, std::string surnames);
    std::string getId();
    Grade getGrade();
    std::string getNames();
    std::string getSurnames();
    std::string toString();
};
