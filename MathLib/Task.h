#pragma once

struct Task {
private:
	int num_1;
	int num_2;
	char operation;
	int answer;
public:
	Task();
	Task(int min, int max, char operation = '\0');

};