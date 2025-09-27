#include <string>

class Teacher {
  private:
    std::string id;
    std::string names;
    std::string surnames;
    int age;

  public:
    Teacher(std::string id, std::string names, std::string surnames, int age);
    std::string getId();
    std::string getNames();
    std::string getSurnames();
    int getAge();
    std::string toString();
};
