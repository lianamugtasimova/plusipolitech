#pragma once
#include <vector>
#include "Equation.h"

class Answer {
public:
	Equation equation;
	std::vector<double> roots;
	std::string studentName;
	Answer(Equation equation, std::vector<double> roots, std::string studentName);
};