#include "pch.h"
#include "MathTest.h"
#include <string>
#include <stdexcept>

TEST(MathTest, ConstructorByCount) {
    MathTest t(5);
    EXPECT_EQ(t.get_count(), 5);
    EXPECT_EQ(t.get_correct_count(), 0);
    for (int i = 0; i < 5; ++i) {
        EXPECT_FALSE(t.is_answered(i));
    }
}

TEST(MathTest, ConstructorByCountAndRange) {
    for (int k = 0; k < 20; ++k) {
        MathTest t(4, 10, 20);
        EXPECT_EQ(t.get_count(), 4);
        for (int i = 0; i < 4; ++i) {
            const Task& task = t.get_task(i);
            EXPECT_GE(task.get_num_1(), 10);
            EXPECT_LE(task.get_num_1(), 20);
            EXPECT_GE(task.get_num_2(), 10);
            EXPECT_LE(task.get_num_2(), 20);
        }
    }
}

TEST(MathTest, ConstructorWithOperationPlus) {
    MathTest t(10, 1, 50, '+');
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(t.get_task(i).get_operation(), '+');
    }
}

TEST(MathTest, ConstructorWithOperationMinus) {
    MathTest t(10, 1, 50, '-');
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(t.get_task(i).get_operation(), '-');
    }
}

TEST(MathTest, ConstructorWithOperationMultiply) {
    MathTest t(10, 1, 9, '*');
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(t.get_task(i).get_operation(), '*');
    }
}

TEST(MathTest, ConstructorWithOperationDivide) {
    MathTest t(10, 1, 100, '/');
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(t.get_task(i).get_operation(), '/');
    }
}

TEST(MathTest, ThrowsOnZeroCount) {
    EXPECT_THROW(MathTest(0), std::invalid_argument);
}

TEST(MathTest, ThrowsOnNegativeCount) {
    EXPECT_THROW(MathTest(-5), std::invalid_argument);
}

TEST(MathTest, ThrowsOnBadRange) {
    EXPECT_THROW(MathTest(3, 100, 1), std::invalid_argument);
}

TEST(MathTest, NotAnsweredInitially) {
    MathTest t(4, 1, 9, '+');
    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(t.is_answered(i));
    }
}

TEST(MathTest, SubmitCorrectAnswer) {
    MathTest t(3, 1, 9, '+');
    int right = t.get_task(0).get_answer();
    t.submit_answer(0, right);
    EXPECT_TRUE(t.is_answered(0));
    EXPECT_EQ(t.get_user_answer(0), right);
    EXPECT_EQ(t.get_correct_count(), 1);
}

TEST(MathTest, SubmitWrongAnswer) {
    MathTest t(3, 1, 9, '+');
    int right = t.get_task(0).get_answer();
    t.submit_answer(0, right + 100);
    EXPECT_TRUE(t.is_answered(0));
    EXPECT_EQ(t.get_user_answer(0), right + 100);
    EXPECT_EQ(t.get_correct_count(), 0);
}

TEST(MathTest, AllCorrectCount) {
    MathTest t(5, 1, 9, '+');
    for (int i = 0; i < 5; ++i) {
        t.submit_answer(i, t.get_task(i).get_answer());
    }
    EXPECT_EQ(t.get_correct_count(), 5);
}

TEST(MathTest, AllWrongCount) {
    MathTest t(5, 1, 9, '+');
    for (int i = 0; i < 5; ++i) {
        t.submit_answer(i, t.get_task(i).get_answer() + 100);
    }
    EXPECT_EQ(t.get_correct_count(), 0);
}

TEST(MathTest, ResubmitSameQuestion) {
    MathTest t(2, 1, 9, '+');
    int right = t.get_task(0).get_answer();
    t.submit_answer(0, right);
    EXPECT_EQ(t.get_correct_count(), 1);
    t.submit_answer(0, right + 100);
    EXPECT_EQ(t.get_correct_count(), 0);
    t.submit_answer(0, right);
    EXPECT_EQ(t.get_correct_count(), 1);
}

TEST(MathTest, SubmitOutOfRange) {
    MathTest t(3, 1, 9, '+');
    EXPECT_THROW(t.submit_answer(-1, 0), std::out_of_range);
    EXPECT_THROW(t.submit_answer(3, 0), std::out_of_range);
}

TEST(MathTest, MarkA) {
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 10; ++i) t.submit_answer(i, t.get_task(i).get_answer());
    EXPECT_EQ(t.get_mark(), 'A');
}

TEST(MathTest, MarkB) {
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 8; ++i) t.submit_answer(i, t.get_task(i).get_answer());
    EXPECT_EQ(t.get_mark(), 'B');
}

TEST(MathTest, MarkC) {
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 7; ++i) t.submit_answer(i, t.get_task(i).get_answer());
    EXPECT_EQ(t.get_mark(), 'C');
}

TEST(MathTest, MarkD) {
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 6; ++i) t.submit_answer(i, t.get_task(i).get_answer());
    EXPECT_EQ(t.get_mark(), 'D');
}

TEST(MathTest, MarkF) {
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 5; ++i) t.submit_answer(i, t.get_task(i).get_answer());
    EXPECT_EQ(t.get_mark(), 'F');
}

TEST(MathTest, MarkFWhenNothingAnswered) {
    MathTest t(10, 1, 9, '+');
    EXPECT_EQ(t.get_mark(), 'F');
}

TEST(MathTest, QuestionTextPlus) {
    MathTest t(1, 10, 20, '+');
    const Task& task = t.get_task(0);
    std::string expected = std::to_string(task.get_num_1()) + " + "
        + std::to_string(task.get_num_2());
    EXPECT_EQ(t.question_text(0), expected);
}

TEST(MathTest, QuestionTextMinus) {
    MathTest t(1, 10, 20, '-');
    const Task& task = t.get_task(0);
    std::string expected = std::to_string(task.get_num_1()) + " - "
        + std::to_string(task.get_num_2());
    EXPECT_EQ(t.question_text(0), expected);
}

TEST(MathTest, QuestionTextMultiply) {
    MathTest t(1, 1, 9, '*');
    const Task& task = t.get_task(0);
    std::string expected = std::to_string(task.get_num_1()) + " * "
        + std::to_string(task.get_num_2());
    EXPECT_EQ(t.question_text(0), expected);
}

TEST(MathTest, QuestionTextDivide) {
    MathTest t(1, 1, 100, '/');
    const Task& task = t.get_task(0);
    std::string expected = std::to_string(task.get_num_1()) + " / "
        + std::to_string(task.get_num_2());
    EXPECT_EQ(t.question_text(0), expected);
}

TEST(MathTest, StatisticsHasAllRows) {
    MathTest t(3, 1, 9, '+');
    t.submit_answer(0, t.get_task(0).get_answer());
    t.submit_answer(1, t.get_task(1).get_answer() + 100);
    t.submit_answer(2, t.get_task(2).get_answer());

    std::string s = t.build_statistics();
    EXPECT_NE(s.find("No"), std::string::npos);
    EXPECT_NE(s.find("Question"), std::string::npos);
    EXPECT_NE(s.find("True Answer"), std::string::npos);
    EXPECT_NE(s.find("Your Answer"), std::string::npos);
    EXPECT_NE(s.find("Result"), std::string::npos);
}

TEST(MathTest, StatisticsTotal) {
    MathTest t(3, 1, 9, '+');
    t.submit_answer(0, t.get_task(0).get_answer());
    t.submit_answer(1, t.get_task(1).get_answer() + 100);
    t.submit_answer(2, t.get_task(2).get_answer());

    std::string s = t.build_statistics();
    EXPECT_NE(s.find("Total Result: 2 / 3 (mark: D)"), std::string::npos);
}

TEST(MathTest, StatisticsUnansweredShowsDash) {
    MathTest t(2, 1, 9, '+');
    t.submit_answer(0, t.get_task(0).get_answer());
    std::string s = t.build_statistics();
    EXPECT_NE(s.find(" - "), std::string::npos);
}

TEST(MathTest, ManyConstructDestruct) {
    for (int n = 1; n <= 30; ++n) {
        MathTest t(n, 1, 50, '+');
        EXPECT_EQ(t.get_count(), n);
    }
}