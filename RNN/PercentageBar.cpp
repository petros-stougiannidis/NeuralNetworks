#include "PercentageBar.h"

PercentageBar::PercentageBar() : percent(0), step(1) {

}

void PercentageBar::print_progress(const int& current_iteration, const int& total_iterations) {
	int current_percent = (current_iteration+1) * 100 / total_iterations;
	if (percent != current_percent) {
		percent = current_percent;
		std::cout << "\r";
		std::cout << "[" << std::string(percent / 2, (char)254u) << std::string(100 / 2 - percent / 2, ' ') << "] ";
		std::cout << percent << "% ";
	}
}

void PercentageBar::reset() {
	percent = 0;
}