#ifndef INSTITUTE_H
#define INSTITUTE_H

#include "learner.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <optional>

class Institute {
private:
    std::vector<Learner> learners;

    // Index: course → set of learner indices with grade >= 9
    std::unordered_map<std::string, std::set<size_t>> highGradeIndex;

    // Helper: safe string-to-int conversion
    static std::optional<int> safeStoi(const std::string &s);

    // Parse past courses (e.g., "DBMS:8|OOPS:9")
    void parsePastCourses(const std::string &str, Learner &l);

    // Parse active courses (e.g., "CN|ML|101")
    void parseActiveCourses(const std::string &str, Learner &l);

public:
    Institute() = default;

    // Load learners from CSV file
    bool loadFromCSV(const std::string &filename);

    // Build index for high-grade learners
    void buildHighGradeIndex();

    // Query learners having grade >= 9 in all given courses
    std::vector<size_t> queryHighGrades(const std::vector<std::string> &courses) const;

    // Display all learners (original order)
    void displayOriginal() const;

    // Return learners
    const std::vector<Learner>& getLearners() const { return learners; }
};

#endif
