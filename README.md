# Learner Management & Multithreaded Sorting System

A C++ project that loads learner data from CSV, parses academic records, performs high-grade queries, and sorts learners using a multithreaded merge sort implementation.

This README fully documents the architecture, workflow, and usage of your system based on all project files.

---

## 🚀 Project Overview

This program manages academic learner data using object-oriented structures and offers:

* **CSV import of learner data** via `Institute` class
* **Parsing of past and active courses**, including numeric and string-based course codes
* **High-grade indexing** (grade ≥ 9) for fast multi-course queries
* **Multithreaded parallel sorting** of learner names using merge sort
* **Interactive CLI menu** for performing all operations

The system is modularized across header + source files with clean separation of responsibility.

---

## 📂 Project Structure

```
/project
│
├── includes/
│   ├── learner.h
│   ├── institute.h
│   ├── multithread_sorter.h
│
├── src/
│   ├── learner.cpp
│   ├── institute.cpp
│   ├── multithread_sorter.cpp
│   ├── main.cpp
│
├── students.csv
├── Makefile
└── README.md
```

---

## 🧩 Component Breakdown

### 1️⃣ **Learner Class** (learner.h / learner.cpp)

Handles all information about a learner, including:

* Full name
* ID (supports **int or string** using `std::variant`) fileciteturn0file1
* Department
* Enrollment year
* Past courses with grades (map<string, int>)
* Active courses (variant of `Course<string>` or `Course<int>`)

It also provides:

* `addPastCourse()` & `addActiveCourse()`
* `getGrade()` using optional
* `hasCourseWithHighGrade()` for grade threshold checks
* `display()` for formatted console printing fileciteturn0file4

---

### 2️⃣ **Institute Class** (institute.h / institute.cpp)

Responsible for reading CSV, storing learners, and building efficient query structures.

Key abilities:

* `loadFromCSV(filename)` to import learner rows
* `parsePastCourses()` for patterns like `DBMS:9|OOPS:8`
* `parseActiveCourses()` for numeric or string course codes (e.g., `ML|101`) fileciteturn0file3
* `buildHighGradeIndex()` to map each course → learners with grade ≥ 9
* `queryHighGrades({course1, course2...})` to find learners with high grades in **all** listed courses
* `displayOriginal()` prints learners in original CSV order

---

### 3️⃣ **MultiThreadSorter** (multithread_sorter.h / .cpp)

A **parallel merge-sort** implementation that:

* Spawns **two threads** to sort left and right halves of the learner list
* Measures and prints per-thread execution time
* Merges final results in main thread

Sorting key = learner full name. fileciteturn0file5

---

### 4️⃣ **Main Program** (main.cpp)

Provides an interactive CLI menu with options: fileciteturn0file5

1. Load learners from CSV
2. Sort learners (parallel)
3. Display original order
4. Display sorted order
5. Query learners with grade ≥ 9 in given courses
6. Exit

---

## 📥 CSV Format

Your CSV must follow:

```
Name, ID, Department, EnrollmentYear, PastCourses, ActiveCourses
```

Example:

```
Alice,2021012,CSE,2021,DBMS:9|OOPS:8,ML|CN|101
```

* **PastCourses** uses `course:grade` pairs
* **ActiveCourses** uses course codes separated by `|`

---

## ⚙️ Building the Project

Use the provided Makefile.

### Build

```
make
```

### Clean

```
make clean
```

### Run

```
./app
```

---

## 🖥️ Program Usage

After running:

```
./app
```

You will see:

```
1. Load learners from CSV
2. Sort learners (parallel sort)
3. Display learners (original order)
4. Display learners (so
```

