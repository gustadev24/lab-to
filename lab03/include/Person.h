#pragma once
#include <string>

class Person {
  protected:
    std::string id;
    std::string names;
    std::string surnames;

  public:
    Person(std::string id, std::string names, std::string surnames);
    std::string getId();
    std::string getNames();
    std::string getSurnames();
    virtual std::string toString();

    bool operator==(const Person& other) const;
};
