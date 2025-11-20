#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

#include "../includes/learner.h"
#include "../includes/institute.h"
#include "../includes/multithread_sorter.h"

void printMenu() {
    std::cout << "\n==================== MENU ====================\n"
              << "1. Load learners from CSV\n"
              << "2. Sort learners (parallel sort)\n"
              << "3. Display learners (original order)\n"
              << "4. Display learners (sorted order)\n"
              << "5. Query learners (grade >= 9 in given courses)\n"
              << "6. Exit\n"
              << "==============================================\n"
              << "Enter choice: ";
}

int main() {
    Institute institute;
    std::vector<Learner> sortedLearners;
    bool sorted = false;

    while (true) {
        printMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        if (choice == 1) {
            std::string filename;
            std::cout << "Enter CSV filename: ";
            std::getline(std::cin, filename);

            if (institute.loadFromCSV(filename)) {
                std::cout << "[Success] Loaded learners from " << filename << "\n";
                sorted = false;
            } else {
                std::cout << "[Error] Failed to load file.\n";
            }
        }

        else if (choice == 2) {
            const auto &learners = institute.getLearners();
            if (learners.empty()) {
                std::cout << "[Error] No learners loaded.\n";
                continue;
            }

            sortedLearners = learners;  // copy original
            MultiThreadSorter::parallelSort(sortedLearners);
            sorted = true;

            std::cout << "[Info] Sorting complete.\n";
        }

        else if (choice == 3) {
            const auto &learners = institute.getLearners();
            if (learners.empty()) {
                std::cout << "[Error] No learners loaded.\n";
                continue;
            }

            std::cout << "\n--- ORIGINAL ORDER ---\n";
            institute.displayOriginal();
        }

        else if (choice == 4) {
            if (!sorted) {
                std::cout << "[Error] You must sort first (choose option 2)\n";
                continue;
            }

            std::cout << "\n--- SORTED ORDER ---\n";
            for (const auto &l : sortedLearners) {
                l.display();
            }
        }

        else if (choice == 5) {
            const auto &learners = institute.getLearners();
            if (learners.empty()) {
                std::cout << "[Error] No learners loaded.\n";
                continue;
            }

            std::cout << "Enter course names (space separated): ";
            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);
            std::vector<std::string> courses;
            std::string course;
            while (ss >> course) courses.push_back(course);

            if (courses.empty()) {
                std::cout << "[Error] No courses provided.\n";
                continue;
            }

            auto indices = institute.queryHighGrades(courses);

            if (indices.empty()) {
                std::cout << "[Info] No learners found with grade >= 9 in ALL given courses.\n";
                continue;
            }

            std::cout << "\n--- QUERY RESULTS ---\n";
            for (size_t idx : indices) {
                learners[idx].display();
            }
        }

        else if (choice == 6) {
            std::cout << "Exiting program.\n";
            break;
        }

        else {
            std::cout << "[Error] Invalid option.\n";
        }
    }

    return 0;
}
