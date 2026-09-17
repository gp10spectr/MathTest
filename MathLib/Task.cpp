#include "Task.h"
#include <random>

int Task::get_num_1() const {
	return num_1;
}

int Task::get_num_2() const {
	return num_2;
}

char Task::get_operation() const {
	return operation;
}

int Task::get_answer() const {
	return answer;
}

//operation 1 -> + operation 2 -> - operation 3 -> * operation 4 -> /
Task::Task() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);
	std::uniform_int_distribution<> dist_operation(1, 4);
	num_1 = dist(gen);
	num_2 = dist(gen);
	int random_operation = dist_operation(gen);
	switch (random_operation) {
	case 1:
		operation = '+';
		answer = num_1 + num_2;
		break;
	case 2:
		operation = '-';
		answer = num_1 - num_2;
		break;
	case 3:
		operation = '*';
		answer = num_1 * num_2;
		break;
	case 4:
		operation = '/';
		if ((num_2 != 0) && (num_1 % num_2 == 0)) {
			answer = num_1 / num_2;
		}
		else {
			while ((num_2 == 0) || (num_1 % num_2 != 0)) {
				num_1 = dist(gen);
				num_2 = dist(gen);
			}
			answer = num_1 / num_2;
		}
		break;
	}
}

Task::Task(int min, int max, char start_operation = '\0') {
	int random_operation;
	if (start_operation != '+' && start_operation != '-' && start_operation != '*' && start_operation != '/')
		start_operation = '\0';
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	std::uniform_int_distribution<> dist_operation(1, 4);
	num_1 = dist(gen);
	num_2 = dist(gen);
	if (start_operation == '\0') {
		random_operation = dist_operation(gen);
		switch (random_operation) {
		case 1:
			operation = '+';
			answer = num_1 + num_2;
			break;
		case 2:
			operation = '-';
			answer = num_1 - num_2;
			break;
		case 3:
			operation = '*';
			answer = num_1 * num_2;
			break;
		case 4:
			operation = '/';
			while ((num_2 == 0) || (num_1 % num_2 != 0)) {
				num_1 = dist(gen);
				num_2 = dist(gen);
			}
			answer = num_1 / num_2;
			break;
		}
	}
	else {
		switch (start_operation) {
		case '+':
			operation = '+';
			answer = num_1 + num_2;
			break;
		case '-':
			operation = '-';
			answer = num_1 - num_2;
			break;
		case '*':
			operation = '*';
			answer = num_1 * num_2;
			break;
		case '/':
			operation = '/';
			while ((num_2 == 0) || (num_1 % num_2 != 0)) {
				num_1 = dist(gen);
				num_2 = dist(gen);
			}
			answer = num_1 / num_2;
			break;
		}
	}

}
