#include "Grade.h"

#include <iostream>

void Grade::recordSolution(const std::string& studentName, int correctSolutions) {
    studentScores[studentName] += correctSolutions;
}

void Grade::publish() const {
    std::cout << "Gradebook" << std::endl;
    for (const auto& student : studentScores) {
        std::cout << student.first << ": " << student.second << " correct solutions" << std::endl;
    }
}