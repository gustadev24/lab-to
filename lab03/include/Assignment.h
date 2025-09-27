#include <optional>
#include <string>
#include "Student.h"
#include "Course.h"

class Assignment {
  private:
    std::string id;
    std::string name;
    std::optional<std::string> presentationDate;
    bool isPresented;

    Student student;
    Course course;
};
