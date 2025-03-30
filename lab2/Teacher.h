#pragma once
#include "Answer.h"
#include "Grade.h"
#include <queue>
#include <map>
#include <string>

class Teacher {
public:
    Grade gradebook;
    std::queue<Answer> answersQueue;
    Teacher();

    void checkAnswer(const Answer& answer);
    void publishGradebook() const;
};
