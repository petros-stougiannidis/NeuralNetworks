#pragma once
#include <iostream>

class PercentageBar {

private:

	int percent;
	int step;

public:

	PercentageBar();
	void print_progress(const int& current_iteration, const int& total_iterations);
	void reset();
};

