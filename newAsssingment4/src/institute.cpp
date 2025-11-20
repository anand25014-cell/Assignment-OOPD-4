#include "../includes/institute.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// ---------------- safeStoi ----------------
std::optional<int> Institute::safeStoi(const std::string &s) {
    try {
        size_t idx;
        int val = std::stoi(s, &idx);
        if (idx != s.size()) return std::nullopt; // Extra characters present
        return val;
    } catch (...) {
        return std::nullopt;
    }
}

// ---------------- parsePastCourses ----------------
void Institute::parsePastCourses(const std::string &str, Learner &l) {
    if (str.empty()) return;

    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, '|')) {
        auto pos = token.find(':');
        if (pos == std::string::npos) continue;

        std::string cname = token.substr(0, pos);
        std::string gstr = token.substr(pos + 1);

        auto g = safeStoi(gstr);
        if (!g.has_value()) continue;

        l.addPastCourse(cname, g.value());
    }
}

// ---------------- parseActiveCourses ----------------
void Institute::parseActiveCourses(const std::string &str, Learner &l) {
    if (str.empty()) return;

    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, '|')) {
        if (token.empty()) continue;

        auto code = safeStoi(token);
        if (code.has_value()) 
            l.addActiveCourse(Course<int>(code.value()));
        else 
            l.addActiveCourse(Course<std::string>(token));
    }
}

// ---------------- loadFromCSV ----------------
bool Institute::loadFromCSV(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Error] Could not open file: " << filename << "\n";
        return false;
    }

    learners.clear(); // Avoid duplicates
    highGradeIndex.clear();

    std::string line;
    std::getline(file, line); // Skip header row

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, idStr, branch, yearStr, pastStr, currStr;

        std::getline(ss, name, ',');
        std::getline(ss, idStr, ',');
        std::getline(ss, branch, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, pastStr, ',');
        std::getline(ss, currStr, ',');

        if (name.empty() || idStr.empty() || branch.empty() || yearStr.empty()) {
            std::cerr << "[Warning] Skipping row (missing mandatory fields): " << line << "\n";
            continue;
        }

        // ID parse
        Learner::IDType id;
        auto idInt = safeStoi(idStr);
        if (idInt.has_value()) id = idInt.value();
        else id = idStr;

        // Year parse
        auto yearInt = safeStoi(yearStr);
        if (!yearInt.has_value()) {
            std::cerr << "[Warning] Invalid year for row: " << line << "\n";
            continue;
        }

        Learner L(name, id, branch, yearInt.value());

        // Parse course data fields
        parsePastCourses(pastStr, L);
        parseActiveCourses(currStr, L);

        learners.push_back(L);
    }

    buildHighGradeIndex();
    return true;
}

// ---------------- buildHighGradeIndex ----------------
void Institute::buildHighGradeIndex() {
    highGradeIndex.clear();

    for (size_t i = 0; i < learners.size(); ++i) {
        for (const auto &p : learners[i].getPastGrades()) {
            if (p.second >= 9) {
                highGradeIndex[p.first].insert(i);
            }
        }
    }
}

// ---------------- queryHighGrades ----------------
std::vector<size_t> Institute::queryHighGrades(const std::vector<std::string> &courses) const {
    if (courses.empty()) return {};

    // Start with first course index
    const auto &firstCourse = courses[0];

    if (!highGradeIndex.count(firstCourse)) return {};

    std::set<size_t> result = highGradeIndex.at(firstCourse);

    // Intersect with remaining course sets
    for (size_t i = 1; i < courses.size(); ++i) {
        const auto &c = courses[i];
        if (!highGradeIndex.count(c)) return {};

        std::set<size_t> temp;

        std::set_intersection(
            result.begin(), result.end(),
            highGradeIndex.at(c).begin(), highGradeIndex.at(c).end(),
            std::inserter(temp, temp.begin())
        );

        result = std::move(temp);
    }

    return std::vector<size_t>(result.begin(), result.end());
}

// ---------------- displayOriginal ----------------
void Institute::displayOriginal() const {
    for (const auto &l : learners) {
        l.display();
    }
}
