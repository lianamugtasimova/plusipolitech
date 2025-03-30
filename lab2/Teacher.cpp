#include "Teacher.h"
#include <iostream>
#include <algorithm>

Teacher::Teacher() {}

void Teacher::checkAnswer(const Answer& answer) {
    Equation equation = answer.equation;
    std::vector<double> studentRoots = answer.roots;
    std::vector<double> correctRoots = equation.solve();

    bool correct = false;
    if (correctRoots.size() == studentRoots.size()) {
        if (correctRoots.empty()) {
            correct = true; 
        }
        else {
            std::sort(studentRoots.begin(), studentRoots.end());
            std::sort(correctRoots.begin(), correctRoots.end());
            correct = (studentRoots == correctRoots);
        }
    }

    if (correct) {
        gradebook.recordSolution(answer.studentName, 1);
    }
    else gradebook.recordSolution(answer.studentName, 0);
}

void Teacher::publishGradebook() const {
    gradebook.publish();
}