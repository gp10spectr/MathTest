#pragma once

struct Task {
private:
	int num_1;
	int num_2;
	char operation;
	int answer;
public:
	int get_num_1() const;
	int get_num_2() const;
	char get_operation() const;
	int get_answer() const;
	Task();
	Task(int min, int max, char operation);

};