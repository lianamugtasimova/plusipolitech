#include "Student.h"
#include <random>

Student::Student(std::string name, SkillLevel skill, double success_rate)
    : name(name), skill(skill), success_rate(success_rate) {}

Answer Student::solveEquation(const Equation& equation) const {
    std::vector<double> correctRoots = equation.solve();

    if (skill == SkillLevel::GOOD) {
        return Answer(equation, correctRoots, name);
    }
    else if (skill == SkillLevel::AVERAGE) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distrib(0.0, 1.0);

        if (distrib(gen) <= success_rate) { 
            return Answer(equation, correctRoots, name);
        }
        else { 
            std::vector<double> incorrectRoots;
            if (correctRoots.empty()) {
                incorrectRoots = { 1.0, 2.0 };
            }
            else {
                incorrectRoots = { correctRoots[0] + 1.0, correctRoots[0] - 1.0 };
            }
            return Answer(equation, incorrectRoots, name);
        }
    }
    else { 
        return Answer(equation, { 0.0 }, name); 
    }
}