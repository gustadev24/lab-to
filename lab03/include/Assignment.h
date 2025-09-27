#pragma once
#include <optional>
#include <string>

class Student;
class Course;

class Assignment {
  private:
    std::string id;
    std::string name;
    std::optional<std::string> presentationDate;
    bool _isPresented;

    Student* student;
    Course* course;
  public:
    Assignment(std::string id, std::string name, Student* student, Course* course);
    std::string getId();
    std::string getName();
    std::optional<std::string> getPresentationDate();
    bool isPresented();
    Student* getStudent();
    Course* getCourse();

    void present();
};
