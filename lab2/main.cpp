#include "Teacher.h"
#include "Student.h"
#include "Equation.h"
#include <fstream>
#include <vector>
#include <string>

int main() {
    Teacher teacher;
    std::vector<Equation> equations = Equation::loadFromFile("equations.txt");

    std::vector<Student> students = {
        {"Vasya Pupkin", SkillLevel::GOOD},
        {"Pupko Vasin", SkillLevel::AVERAGE, 0.6},
        {"Chikatilo", SkillLevel::BAD},
        {"Marilyn Monroe", SkillLevel::AVERAGE, 0.8},
        {"Abay", SkillLevel:: AVERAGE, 0.3}
    };

    for (const auto& student : students) {
        for (const auto& equation : equations) {
            Answer answer = student.solveEquation(equation);
            teacher.answersQueue.push(answer);
        }
    }

    while (!teacher.answersQueue.empty()) {
        Answer answer = teacher.answersQueue.front();
        teacher.answersQueue.pop();
        teacher.checkAnswer(answer);
    }

    teacher.publishGradebook();

    return 0;
}