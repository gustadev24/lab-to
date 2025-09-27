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

    std::string getId() const;
    std::string getName() const;
    std::string toString() const;

    bool operator==(const Grade& other) const;
};

inline const Grade Grade::FIRST = Grade("1", "First");
inline const Grade Grade::SECOND = Grade("2", "Second");
inline const Grade Grade::THIRD = Grade("3", "Third");
inline const Grade Grade::FOURTH = Grade("4", "Fourth");
inline const Grade Grade::FIFTH = Grade("5", "Fifth");
inline const Grade Grade::SIXTH = Grade("6", "Sixth");
