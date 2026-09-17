#pragma once
#include "Task.h"
#include <string>

// mark A/B/C/D/F
// A >= 90%
// B 80 - 89%
// C 70 - 79%
// D 60 - 69%
// F < 60%
class MathTest {
private:
    Task* tasks;
    int   count;
    int* user_answers;
    int   correct_count;
    bool* answered;

    void init(int count, int min, int max, char operation);

public:
    MathTest(int start_count);
    MathTest(int count, int min, int max);
    MathTest(int count, int min, int max, char operation);
    ~MathTest();

    //without that there might be a conflict with default constructor
    MathTest(const MathTest&) = delete;
    MathTest& operator=(const MathTest&) = delete;

    void run();
    void show_statistics();

    void submit_answer(int index, int answer);
    std::string question_text(int index) const;
    std::string build_statistics() const;
    char get_mark() const;

    int get_count() const;
    int get_correct_count() const;
    const Task& get_task(int index) const;
    int get_user_answer(int index) const;
    bool is_answered(int index) const;
};