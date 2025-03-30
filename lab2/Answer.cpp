#include "Answer.h"

Answer::Answer(Equation equation, std::vector<double> roots, std::string studentName) 
	: equation(equation), roots(roots), studentName(studentName) {}