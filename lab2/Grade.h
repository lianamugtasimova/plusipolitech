#pragma once
#include <map>
#include <string>

class Grade {
public:
    void recordSolution(const std::string& studentName, int correctSolutions);
    void publish() const;

private:
    std::map<std::string, int> studentScores;
};