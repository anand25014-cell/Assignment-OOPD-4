#include "../includes/learner.h"
#include <iomanip>

// ----- Constructor -----
Learner::Learner(std::string name,
                 IDType idValue,
                 std::string dept,
                 int year)
    : fullName(std::move(name)),
      id(std::move(idValue)),
      department(std::move(dept)),
      enrollmentYear(year) {}


// ----- Adders -----
void Learner::addPastCourse(const std::string &course, int grade) {
    pastGrades[course] = grade;
}

void Learner::addActiveCourse(const ActiveCourseType &course) {
    activeCourses.push_back(course);
}


// ----- Getters -----
const std::string& Learner::getName() const { return fullName; }

const Learner::IDType& Learner::getID() const { return id; }

const std::string& Learner::getDepartment() const { return department; }

int Learner::getEnrollmentYear() const { return enrollmentYear; }

const std::map<std::string, int>& Learner::getPastGrades() const { return pastGrades; }

// FIXED VERSION (Fully-qualified name)
const std::vector<Learner::ActiveCourseType>& Learner::getActiveCourses() const {
    return activeCourses;
}


// ----- Utility: Get grade of a course -----
std::optional<int> Learner::getGrade(const std::string &course) const {
    auto it = pastGrades.find(course);
    if (it == pastGrades.end()) return std::nullopt;
    return it->second;
}


// ----- Utility: Check if student has grade >= threshold -----
bool Learner::hasCourseWithHighGrade(const std::string &course, int threshold) const {
    auto g = getGrade(course);
    return g.has_value() && g.value() >= threshold;
}


// ----- Display method -----
void Learner::display() const {
    std::cout << "-----------------------------------\n";

    std::cout << "Name           : " << fullName << "\n";

    std::cout << "ID             : ";
    std::visit([](auto &&arg){ std::cout << arg; }, id);
    std::cout << "\n";

    std::cout << "Department     : " << department << "\n";
    std::cout << "Enrollment Year: " << enrollmentYear << "\n";

    std::cout << "Past Courses   : ";
    if (pastGrades.empty()) {
        std::cout << "None";
    } else {
        for (auto &p : pastGrades) {
            std::cout << p.first << "(" << p.second << ") ";
        }
    }
    std::cout << "\n";

    std::cout << "Current Courses: ";
    if (activeCourses.empty()) {
        std::cout << "None";
    } else {
        for (auto &ac : activeCourses) {
            std::visit([](auto &&c){ std::cout << c.value << " "; }, ac);
        }
    }
    std::cout << "\n";
}
