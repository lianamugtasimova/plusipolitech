#pragma once
#include <vector>
#include <string>
#include <fstream>

class Equation {
public:
    double a, b, c;

    Equation(double a, double b, double c);

    std::vector<double> solve() const;

    static std::vector<Equation> loadFromFile(const std::string& filename);
};