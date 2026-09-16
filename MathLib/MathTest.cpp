#include "MathTest.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

static const int LABEL_W = 11; //True answer = 11
static const int CELL_W = 9; // answer field width

static std::string fit(const std::string& s, int w) {
    std::ostringstream os;
    os << std::setw(w) << std::right << s;
    return os.str();
}

static std::string label_cell(const std::string& s) {
    return " " + fit(s, LABEL_W) + " ";
}

static std::string num_cell(const std::string& s) {
    return " " + fit(s, CELL_W) + " ";
}

void MathTest::init(int count, int min, int max, char operation) {
    if (count <= 0)
        throw std::invalid_argument("MathTest: count must be > 0");
    if (min > max)
        throw std::invalid_argument("MathTest: min must be <= max");

    this->count = count;
    this->correct_count = 0;

    tasks = new Task[count];
    user_answers = new int[count];
    answered = new bool[count];

    for (int i = 0; i < count; ++i) {
        tasks[i] = Task(min, max, operation);
        user_answers[i] = 0;
        answered[i] = false;
    }
}

MathTest::MathTest(int start_count) {
    init(start_count, 1, 100, '\0');
}

MathTest::MathTest(int count, int min, int max) {
    init(count, min, max, '\0');
}

MathTest::MathTest(int count, int min, int max, char operation) {
    init(count, min, max, operation);
}

MathTest::~MathTest() {
    delete[] tasks;
    delete[] user_answers;
    delete[] answered;
}

int MathTest::get_count() const { 
    return count;
}

int MathTest::get_correct_count() const { 
    return correct_count;
}

const Task& MathTest::get_task(int index) const { 
    return tasks[index];
}

int MathTest::get_user_answer(int index) const { 
    return user_answers[index];
}

bool MathTest::is_answered(int index) const { 
    return answered[index];
}

std::string MathTest::question_text(int index) const {
    const Task& t = tasks[index];
    std::ostringstream os;
    os << t.get_num_1() << " " << t.get_operation() << " " << t.get_num_2();
    return os.str();
}

void MathTest::submit_answer(int index, int answer) {
    if (index < 0 || index >= count)
        throw std::out_of_range("index out of range");

    const bool was_correct = answered[index] && user_answers[index] == tasks[index].get_answer();
    const bool now_correct = (answer == tasks[index].get_answer());

    user_answers[index] = answer;
    answered[index] = true;

    if (!was_correct && now_correct)      ++correct_count;
    else if (was_correct && !now_correct) --correct_count;
}

char MathTest::get_mark() const {
    if (count <= 0) return 'F';
    const double pct = 100.0 * correct_count / count;
    if (pct >= 90.0)
        return 'A';
    if (pct >= 80.0)
        return 'B';
    if (pct >= 70.0)
        return 'C';
    if (pct >= 60.0)
        return 'D';
    return 'F';
}

std::string MathTest::build_statistics() const {
    std::ostringstream os;

    // top part
    std::string header = "|" + label_cell("No");
    for (int i = 0; i < count; ++i)
        header += "|" + num_cell(std::to_string(i + 1));
    header += "|";
    os << header << "\n";

    // collumn
    os << std::string(header.size(), '-') << "\n";

    // questions
    std::string row_q = "|" + label_cell("Question");
    for (int i = 0; i < count; ++i)
        row_q += "|" + num_cell(question_text(i));
    row_q += "|";
    os << row_q << "\n";

    // true answers
    std::string row_t = "|" + label_cell("True Answer");
    for (int i = 0; i < count; ++i)
        row_t += "|" + num_cell(std::to_string(tasks[i].get_answer()));
    row_t += "|";
    os << row_t << "\n";

    // user answers
    std::string row_u = "|" + label_cell("Your Answer");
    for (int i = 0; i < count; ++i) {
        std::string cell = answered[i] ? std::to_string(user_answers[i]) : "-";
        row_u += "|" + num_cell(cell);
    }
    row_u += "|";
    os << row_u << "\n";

    std::string row_r = "|" + label_cell("Result");
    for (int i = 0; i < count; ++i) {
        const bool ok = answered[i] && user_answers[i] == tasks[i].get_answer();
        row_r += "|" + num_cell(std::string(1, ok ? '+' : '-'));
    }
    row_r += "|";
    os << row_r << "\n";

    os << "\nTotal Result: " << correct_count << " / " << count
        << " (mark: " << get_mark() << ")\n";

    return os.str();
}

void MathTest::show_statistics() {
    std::cout << build_statistics();
}

void MathTest::run() {
    for (int i = 0; i < count; ++i) {
        user_answers[i] = 0;
        answered[i] = false;
    }
    correct_count = 0;

    std::cout << "Test of " << count << " questions.\n";
    for (int i = 0; i < count; ++i) {
        std::cout << "Q" << (i + 1) << ": " << question_text(i) << " = ? ";
        int a = 0;
        if (!(std::cin >> a)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "wrong input\n";
            a = 0;
        }
        submit_answer(i, a);
    }

    std::cout << "\n";
    show_statistics();
}