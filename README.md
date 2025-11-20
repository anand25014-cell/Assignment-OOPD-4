# 🎓 Learner Management & Multithreaded Sorting System

A complete ERP-style academic data management system supporting **multiple universities**, **multiple data types**, **parallel sorting**, and **high‑grade queries**.

This README explains **how every requirement is implemented**, with icons, diagrams, and references to where the code lives.

---

# 📌 **System Architecture Overview**

```
           +-------------------+
           |     CSV File      |
           +-------------------+
                     |
                     v
     +-------------------------------+
     |          Institute            |
     |  (Parsing, Indexing, Query)  |
     +-------------------------------+
          | learners[] vector
          v
 +-----------------+         +---------------------+
 |     Learner     |<------->|   Course<T> (int/str)|
 +-----------------+         +---------------------+
          |
          v
 +------------------------+
 | MultiThreadSorter      |
 | (Parallel Merge Sort)  |
 +------------------------+
```

---

# ✅ **1. Handling Multiple Universities & Data Types**

### ✔ Requirement

ERP must support:

* Roll numbers = `string` **or** `integer`
* Course codes = `string` **or** `integer`
* Without needing separate classes

### ✔ Implementation Location

📌 **File:** `learner.h`
📌 **Feature:** **`std::variant`-based flexible types**

### 🔧 How It Works

```cpp
typedef std::variant<int, std::string> IDType;                     // Roll Number

using ActiveCourseType = std::variant<Course<std::string>, Course<int>>; // Course Codes

template <typename T>
struct Course {
    T value;
};
```

### 🎯 Why This Works

Your `Learner` class can now store:

* IIIT-Delhi style → `DBMS`, `OOPS`, `AI`
* IIT-Delhi style → `101`, `204`, `305`

**Automatically. No duplication of classes.**

---

# ✅ **2. Parsing Both Numeric & String Course Codes Automatically**

### ✔ Requirement

Handle both course code systems transparently.

### ✔ Implementation Location

📌 **File:** `institute.cpp` → `parseActiveCourses()`

### 🔧 How It Works

```cpp
auto code = safeStoi(token);
if (code.has_value())
    l.addActiveCourse(Course<int>(code.value()));   // IIT-Delhi style
else
    l.addActiveCourse(Course<std::string>(token));  // IIIT-Delhi style
```

### 🎯 What This Achieves

* Detects if a course code is integer or string.
* Saves it in the correct type.
* No user input required.

---

# ✅ **3. Storing, Viewing & Querying Learner Records**

### ✔ Requirement

* Show learners **in the order entered**.
* Show learners **in sorted order**, *without modifying original data*.
* Use different iterator flows.

### ✔ Implementation Location

📌 **File:** `main.cpp`
📌 **File:** `institute.cpp`

### 🔧 Original Order

```cpp
institute.displayOriginal();
```

Uses **range-based vector iterators**:

```cpp
for (const auto &l : learners) { ... }
```

### 🔧 Sorted Order

```cpp
sortedLearners = learners;
MultiThreadSorter::parallelSort(sortedLearners);
```

Uses new iterators over the **sorted copy**.

### 🎯 Why This Meets Requirement

* Original `learners` vector stays untouched.
* `sortedLearners` uses independent iteration.
* Two traversal modes = two iterator types.

---

# ✅ **4. Parallel Sorting Using MultiThreadSorter**

### ✔ Requirement

Sort with **two threads**, faster than serial sorting.

### ✔ Implementation Location

📌 **File:** `multithread_sorter.cpp` → `parallelSort()`

### 🔧 How Sorting Works

```
      +-------------+         +-------------+
      |  Thread 1   |         |  Thread 2   |
      | Sort Left   |         | Sort Right  |
      +-------------+         +-------------+
                \               /
                 \             /
                  v           v
                +---------------+
                |   Main Thread |
                | Merge Halves  |
                +---------------+
```

### 🔧 Key Code

```cpp
std::thread t1(t1Func);
std::thread t2(t2Func);

t1.join();
t2.join();
merge(arr, 0, mid - 1, n - 1);
```

### 🎯 Achievements

* True parallel processing.
* Much faster on large learner lists.
* Clean separation: thread work + final merge.

---

# ✅ **5. High-Grade Query System (Grade ≥ 9)**

### ✔ Requirement

Return learners who scored **≥9** in **all selected courses**.

### ✔ Implementation Location

📌 **File:** `institute.cpp` → `buildHighGradeIndex()` & `queryHighGrades()`

### 🔧 Indexing Structure

```
course_name → set of learner indices with grade ≥ 9
```

### Example

```
DBMS → {0,2,3}
OOPS → {1,3}

Query(DBMS, OOPS) → intersection = {3}
```

### 🔧 Core Code

```cpp
std::set_intersection(
   result.begin(), result.end(),
   highGradeIndex.at(c).begin(),
   highGradeIndex.at(c).end(),
   std::inserter(temp, temp.begin())
);
```

### 🎯 Achievements

* Super-fast queries.
* Works for any number of courses.
* No need to scan all learners repeatedly.

---

# 🧪 **Sample Workflow**

```
1. Load students from CSV
2. Sort the learners in parallel
3. Display original or sorted lists
4. Query learners scoring >=9 in desired courses
```

---

# 📦 **Build & Run Instructions**

### 🛠 Build

```
make
```

### ▶ Run

```
./app
```

### 🧹 Clean

```
make clean
```

---

# 🎯 Summary of Features & Where They Are Implemented

| Feature                                | Implementation                        | File                     |
| -------------------------------------- | ------------------------------------- | ------------------------ |
| Support string/int roll numbers        | `std::variant<int,string>`            | `learner.h`              |
| Support string/int course codes        | `variant<Course<int>,Course<string>>` | `learner.h`              |
| Automatic detection of course type     | `safeStoi` + parser                   | `institute.cpp`          |
| Store original order                   | `learners` vector                     | `institute.h/.cpp`       |
| Sorted view without modifying original | `sortedLearners` copy                 | `main.cpp`               |
| Iterator-based display                 | range-for loops                       | `displayOriginal()`      |
| Parallel sorting                       | merge sort + threads                  | `multithread_sorter.cpp` |
| High-grade queries                     | `highGradeIndex`                      | `institute.cpp`          |

---

# 🏁 Final Notes

Your system implements **all required features beautifully**, using:

* `std::variant` for type‑flexibility
* Template-based course representation
* Multi-threaded merge sort
* Set‑based index for fast high-grade search
* Iterator-based traversal for original & sorted views

If you'd like, I can also add:
✅ UML diagrams
✅ Sequence diagrams
✅ Animated workflow visuals

Just tell me! 🚀


