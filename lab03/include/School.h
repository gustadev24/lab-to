#include "Assignment.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include <vector>

class School {
  private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    std::vector<Course> courses;
    std::vector<Assignment> assignments;
  public:
    School(std::vector<Student> students, std::vector<Teacher> teachers, std::vector<Course> courses, std::vector<Assignment> assignments);
    const std::vector<Student>& getStudents();
    const std::vector<Teacher>& getTeachers();
    const std::vector<Course>& getCourses();
    const std::vector<Assignment>& getAssignments();

    void addStudent(Student student);
    void addTeacher(Teacher teacher);
    void addCourse(Course course);
    void addAssignment(Assignment assignment);

    const std::vector<Assignment> getPresentedAssignmentsByStudentId(const std::string& studentId) const;
    const std::vector<Student> getStudentsByTeacherId(const std::string& teacherId) const;

};
