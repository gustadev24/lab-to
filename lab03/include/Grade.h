#pragma once
#include <string>
class Grade {
  private:
    std::string id;
    std::string name;

    Grade(std::string id, std::string name);

  public:
    static const Grade FIRST;
    static const Grade SECOND;
    static const Grade THIRD;
    static const Grade FOURTH;
    static const Grade FIFTH;
    static const Grade SIXTH;

    std::string getId();
    std::string getName();
    std::string toString();
};
