#pragma once
#include "Answer.h"
#include <string>

enum class SkillLevel {
    GOOD,
    AVERAGE,
    BAD
};

class Student {
public:
    std::string name;
    SkillLevel skill;
    double success_rate;

    Student(std::string name, SkillLevel skill, double success_rate = 0.0);

    Answer solveEquation(const Equation& equation) const;
};
