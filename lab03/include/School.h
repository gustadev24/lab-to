#include "Assignment.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include <vector>

class School {
  private:
    std::vector<Student*> students;
    std::vector<Teacher*> teachers;
    std::vector<Course*> courses;
    std::vector<Assignment*> assignments;
  public:
    School(std::vector<Student*> students, std::vector<Teacher*> teachers, std::vector<Course*> courses, std::vector<Assignment*> assignments);
    ~School();
    const std::vector<Student*>& getStudents();
    const std::vector<Teacher*>& getTeachers();
    const std::vector<Course*>& getCourses();
    const std::vector<Assignment*>& getAssignments();

    void addStudent(Student* student);
    void addTeacher(Teacher* teacher);
    void addCourse(Course* course);
    void addAssignment(Assignment* assignment);

    const std::vector<Assignment*> getPresentedAssignmentsByStudentId(const std::string& studentId) const;
    const std::vector<Assignment*> getAllAssignmentsByStudentId(const std::string& studentId) const;
    const std::vector<Student*> getStudentsByTeacherId(const std::string& teacherId) const;
    const std::vector<Course*> getCoursesByTeacherId(const std::string& teacherId) const;

    void showAssignmentDeliveryStatistics() const;
    void showTeacherStatistics(const std::string& teacherId) const;

    // Search functions (no printing, return data only)
    Student* searchStudentById(const std::string& studentId) const;
    std::vector<Teacher*> searchTeachersByName(const std::string& teacherName) const;
    std::vector<Student*> searchStudentsByCourse(const std::string& courseId) const;
    Course* searchCourseById(const std::string& courseId) const;

};
