#ifndef LEARNER_H
#define LEARNER_H

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <iostream>
#include <optional>

//
// Generic Course<T> wrapper.
// Used for both IIIT-Delhi course names (string)
// and IIT-Delhi numeric course codes (int).
//
template <typename T>
struct Course {
    T value;
    Course(const T &v) : value(v) {}
};

class Learner {
public:
    using IDType = std::variant<int, std::string>;
    using ActiveCourseType = std::variant<Course<std::string>, Course<int>>;

private:
    std::string fullName;
    IDType id;
    std::string department;
    int enrollmentYear = 0;

    std::map<std::string, int> pastGrades;       // course → grade
    std::vector<ActiveCourseType> activeCourses; // string or int courses

public:
    // Constructors
    Learner() = default;
    Learner(std::string name,
            IDType idValue,
            std::string dept,
            int year);

    // Adders
    void addPastCourse(const std::string &course, int grade);
    void addActiveCourse(const ActiveCourseType &course);

    // Getters
    const std::string& getName() const;
    const IDType& getID() const;
    const std::string& getDepartment() const;
    int getEnrollmentYear() const;
    const std::map<std::string, int>& getPastGrades() const;
    const std::vector<ActiveCourseType>& getActiveCourses() const;

    // Utilities
    std::optional<int> getGrade(const std::string &course) const;
    bool hasCourseWithHighGrade(const std::string &course, int threshold = 9) const;

    // Display
    void display() const;
};

#endif
