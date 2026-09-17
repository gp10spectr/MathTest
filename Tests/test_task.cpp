#include "pch.h"
#include "Task.h"

TEST(Task, InRange) {
    for (int i = 0; i < 100; ++i) {
        Task t;
        EXPECT_GE(t.get_num_1(), 1);
        EXPECT_LE(t.get_num_1(), 100);
        EXPECT_GE(t.get_num_2(), 1);
        EXPECT_LE(t.get_num_2(), 100);
    }
}

TEST(Task, CorrectOperation) {
    for (int i = 0; i < 100; ++i) {
        Task t;
        EXPECT_TRUE(t.get_operation() == '+' || t.get_operation() == '-' || t.get_operation() == '*' || t.get_operation() == '/');
    }
}

TEST(Task, AllOperationsSeen) {
    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;
    for (int i = 0; i < 1000; ++i) {
        Task t;
        switch (t.get_operation()) {
        case '+':
            count_1++;
            break;
        case '-':
            count_2++;
            break;
        case '*':
            count_3++;
            break;
        case '/':
            count_4++;
            break;
        }
    }
    EXPECT_GT(count_1, 0);
    EXPECT_GT(count_2, 0);
    EXPECT_GT(count_3, 0);
    EXPECT_GT(count_4, 0);
}

TEST(Task, CorrectAnswer) {
    for (int i = 0; i < 100; ++i) {
        Task t1(1, 100, '+');
        int true_answer_1 = t1.get_num_1() + t1.get_num_2();
        Task t2(1, 100, '-');
        int true_answer_2 = t2.get_num_1() - t2.get_num_2();
        Task t3(1, 100, '*');
        int true_answer_3 = t3.get_num_1() * t3.get_num_2();
        Task t4(1, 100, '/');
        int true_answer_4 = t4.get_num_1() / t4.get_num_2();
        EXPECT_EQ(true_answer_1, t1.get_answer());
        EXPECT_EQ(true_answer_2, t2.get_answer());
        EXPECT_EQ(true_answer_3, t3.get_answer());
        EXPECT_EQ(true_answer_4, t4.get_answer());
    }
}

TEST(Task, CorrectDivOperation) {
    for (int i = 0; i < 100; ++i) {
        Task t(1, 100, '/');
        ASSERT_NE(t.get_num_2(), 0);
        EXPECT_EQ(t.get_num_1() % t.get_num_2(), 0);
    }
}
